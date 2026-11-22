"use client";
import { useEffect, useRef, useState } from "react";
import { CodeEditor } from "./CodeEditor";

/* Web judge: compiles and runs the submitted C++ on Compiler Explorer (godbolt.org)
   against tests generated at build time by judge/web/build_tests.py. */

type Test = { name: string; input: string; bytes: number; output?: string; count?: number; hash?: string };
type Manifest = { id: string; tests: Test[] };
type Verdict = "waiting" | "skipped" | "running" | "AC" | "WA" | "TLE" | "RE" | "CE" | "ERR";
type Row = { name: string; verdict: Verdict; ms?: number };

const BASE = process.env.NEXT_PUBLIC_BASE_PATH ?? "";
const COMPILER = "g142"; // GCC 14.2
const TIME_LIMIT_MS = 3000;
const TEMPLATE = `#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    return 0;
}
`;

const LABEL: Record<Verdict, string> = {
  waiting: "Waiting",
  skipped: "Not run",
  running: "Running",
  AC: "Accepted",
  WA: "Wrong answer",
  TLE: "Time limit exceeded",
  RE: "Runtime error",
  CE: "Compile error",
  ERR: "Judge unavailable",
};
const COLOR: Record<Verdict, string> = {
  waiting: "bg-line text-muted",
  skipped: "bg-line text-muted",
  running: "bg-head text-head-fg",
  AC: "bg-easy text-white",
  WA: "bg-hard text-white",
  TLE: "bg-medium text-white",
  RE: "bg-hard text-white",
  CE: "bg-hard text-white",
  ERR: "bg-muted text-white",
};

const stripAnsi = (s: string) => s.replace(/\x1b\[[0-9;]*[A-Za-z]/g, "");
const lines = (a?: { text: string }[]) => (a ?? []).map((l) => l.text).join("\n");

async function runOnCompilerExplorer(source: string, stdin: string) {
  const res = await fetch(`https://godbolt.org/api/compiler/${COMPILER}/compile`, {
    method: "POST",
    headers: { "Content-Type": "application/json", Accept: "application/json" },
    body: JSON.stringify({
      source,
      compiler: COMPILER,
      lang: "c++",
      allowStoreCodeDebug: false,
      options: {
        userArguments: "-O2 -std=c++17 -pthread",
        executeParameters: { args: [], stdin },
        compilerOptions: { executorRequest: true },
        filters: { execute: true },
        tools: [],
        libraries: [],
      },
    }),
  });
  if (!res.ok) throw new Error(`Compiler Explorer answered ${res.status}`);
  return res.json();
}

function firstDiff(expected: string[], got: string[]) {
  for (let i = 0; i < Math.min(expected.length, got.length); i++)
    if (expected[i] !== got[i]) return `Token #${i + 1}: expected "${expected[i]}", got "${got[i]}".`;
  return `Expected ${expected.length} tokens, got ${got.length}.`;
}

export function Judge({ id }: { id: string }) {
  const key = `kdcp-code:${id}`;
  const [code, setCode] = useState(TEMPLATE);
  const [rows, setRows] = useState<Row[]>([]);
  const [busy, setBusy] = useState(false);
  const [final, setFinal] = useState<Verdict | null>(null);
  const [detail, setDetail] = useState<{ text: string; input?: string } | null>(null);
  const cache = useRef(new Map<string, string>());

  useEffect(() => {
    try {
      const saved = localStorage.getItem(key);
      if (saved) setCode(saved);
    } catch {}
  }, [key]);

  const save = (v: string) => {
    setCode(v);
    try {
      localStorage.setItem(key, v);
    } catch {}
  };

  const text = async (path: string) => {
    if (!cache.current.has(path)) {
      const r = await fetch(`${BASE}/judge/${path}`);
      if (!r.ok) throw new Error(`Could not load ${path}`);
      cache.current.set(path, await r.text());
    }
    return cache.current.get(path)!;
  };

  async function submit() {
    setBusy(true);
    setFinal(null);
    setDetail(null);
    let manifest: Manifest;
    try {
      manifest = JSON.parse(await text(`${id}/manifest.json`));
    } catch {
      setFinal("ERR");
      setDetail({ text: "The tests for this problem could not be loaded." });
      setBusy(false);
      return;
    }
    const table: Row[] = manifest.tests.map((t) => ({ name: t.name, verdict: "waiting" }));
    setRows([...table]);
    const update = (i: number, r: Partial<Row>) => {
      table[i] = { ...table[i], ...r };
      setRows([...table]);
    };

    let verdict: Verdict = "AC";
    for (let i = 0; i < manifest.tests.length && verdict === "AC"; i++) {
      const t = manifest.tests[i];
      update(i, { verdict: "running" });
      try {
        const stdin = await text(`${id}/${t.input}`);
        const big = t.hash !== undefined;
        // Large outputs are hashed inside the program, since the runner returns at most 32 KB of output.
        const source = big ? `${code}\n${await text("wrapper_tail.cpp")}` : code;
        const r = await runOnCompilerExplorer(source, stdin);
        const ms = r.execTime ? Number(r.execTime) : undefined;

        if (r.buildResult?.code) {
          verdict = "CE";
          setDetail({ text: stripAnsi(lines(r.buildResult.stderr)) });
        } else if (r.timedOut || (ms ?? 0) > TIME_LIMIT_MS) {
          verdict = "TLE";
          setDetail({ text: `Your program ran longer than ${TIME_LIMIT_MS / 1000} s on ${t.name.toLowerCase()}.` });
        } else if (r.code !== 0) {
          verdict = "RE";
          setDetail({ text: `Exit code ${r.code}.\n${stripAnsi(lines(r.stderr))}`.trim(), input: big ? undefined : stdin });
        } else if (big) {
          const m = lines(r.stdout).match(/KDCP (\d+) ([0-9a-f]{16})/);
          if (!m || Number(m[1]) !== t.count || m[2] !== t.hash) {
            verdict = "WA";
            setDetail({
              text:
                m && Number(m[1]) !== t.count
                  ? `Expected ${t.count} tokens, got ${m[1]}.`
                  : "Your output differs from the expected output (this test is too large to show the difference).",
            });
          }
        } else {
          if (r.truncated) {
            verdict = "WA";
            setDetail({ text: "Your program printed far more output than expected." });
          } else {
            const got = lines(r.stdout).split(/\s+/).filter(Boolean);
            const exp = (t.output ?? "").split(/\s+/).filter(Boolean);
            if (got.length !== exp.length || got.some((g, k) => g !== exp[k])) {
              verdict = "WA";
              setDetail({ text: firstDiff(exp, got), input: stdin.length <= 4000 ? stdin : undefined });
            }
          }
        }
        update(i, { verdict, ms });
      } catch (e) {
        verdict = "ERR";
        update(i, { verdict });
        setDetail({ text: `Could not reach the runner: ${(e as Error).message}. Try again in a moment.` });
      }
    }
    table.forEach((r, i) => r.verdict === "waiting" && update(i, { verdict: "skipped" }));
    setFinal(verdict);
    setBusy(false);
  }


  const passed = rows.filter((r) => r.verdict === "AC").length;

  return (
    <section className="mt-14 rounded-xl border border-line bg-card p-5 shadow-sm">
      <div className="flex flex-wrap items-center justify-between gap-2">
        <h2 className="text-[1.05rem] font-bold tracking-tight">Submit</h2>
        <span className="rounded-md border border-line px-2 py-0.5 font-mono text-[11px] text-muted">
          C++17 · GCC 14 · -O2 · {TIME_LIMIT_MS / 1000} s
        </span>
      </div>

      <CodeEditor value={code} onChange={save} onSubmit={() => !busy && submit()} />

      <div className="mt-3 flex flex-wrap items-center gap-3">
        <button
          type="button"
          onClick={submit}
          disabled={busy}
          className="rounded-full bg-easy px-6 py-2 text-sm font-bold text-white transition-opacity hover:opacity-90 disabled:opacity-60"
        >
          {busy ? "Judging…" : "Submit"}
        </button>
        <button
          type="button"
          onClick={() => save(TEMPLATE)}
          disabled={busy}
          className="rounded-full border border-line px-4 py-2 text-sm text-muted transition-colors hover:text-fg"
        >
          Reset code
        </button>
        <span className="text-xs text-muted">Code is compiled and run on godbolt.org (Compiler Explorer).</span>
      </div>

      {rows.length > 0 && (
        <div className="mt-5">
          {final && (
            <div className={`mb-3 flex items-center justify-between rounded-lg px-4 py-2.5 text-sm font-bold ${COLOR[final]}`}>
              <span>{LABEL[final]}</span>
              <span className="font-mono text-xs font-normal opacity-90">
                {passed}/{rows.length} tests
              </span>
            </div>
          )}
          <div className="overflow-hidden rounded-lg border border-line">
            <table className="w-full text-sm">
              <tbody className="divide-y divide-line">
                {rows.map((r) => (
                  <tr key={r.name}>
                    <td className="py-2 pl-4">{r.name}</td>
                    <td className="py-2 text-right font-mono text-xs text-muted">{r.ms !== undefined ? `${r.ms} ms` : ""}</td>
                    <td className="py-2 pl-3 pr-4 text-right">
                      <span className={`inline-block rounded-full px-2.5 py-0.5 text-[11px] font-medium ${COLOR[r.verdict]}`}>
                        {LABEL[r.verdict]}
                      </span>
                    </td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
          {detail && (
            <div className="mt-3 space-y-2">
              <pre className="overflow-x-auto whitespace-pre-wrap rounded-lg border border-line bg-[#f6f7f9] p-3 font-mono text-xs">{detail.text}</pre>
              {detail.input && (
                <>
                  <p className="text-xs font-bold">Input of the failed test</p>
                  <pre className="max-h-56 overflow-auto rounded-lg border border-line bg-[#f6f7f9] p-3 font-mono text-xs">{detail.input}</pre>
                </>
              )}
            </div>
          )}
        </div>
      )}
    </section>
  );
}
