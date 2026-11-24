"use client";
import { useEffect, useRef, useState } from "react";
import { CodeEditor } from "./CodeEditor";

/* HackerRank-style workspace: editor, Run Code (samples) and Submit Code (all tests).
   Code is compiled and run on Compiler Explorer (godbolt.org) against tests generated
   at build time by judge/web/build_tests.py. */

type Test = { name: string; input: string; bytes: number; output?: string; count?: number; hash?: string };
type Manifest = { id: string; tests: Test[] };
type Verdict = "waiting" | "skipped" | "running" | "AC" | "WA" | "TLE" | "RE" | "CE" | "ERR";
type Result = {
  name: string;
  verdict: Verdict;
  ms?: number;
  input?: string; // shown when the test is small
  inputBytes: number;
  expected?: string;
  got?: string;
  message?: string;
};

const BASE = process.env.NEXT_PUBLIC_BASE_PATH ?? "";
const COMPILER = "g142"; // GCC 14.2
const TIME_LIMIT_MS = 3000;
const SHOW_LIMIT = 6000; // characters of input/output shown per test
const TEMPLATE = `#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    int test = 1;
    cin >> test;
    while (test--) {
        solve();
    }
    return 0;
}
`;

const LABEL: Record<Verdict, string> = {
  waiting: "Waiting",
  skipped: "Not run",
  running: "Running",
  AC: "Accepted",
  WA: "Wrong Answer",
  TLE: "Time Limit Exceeded",
  RE: "Runtime Error",
  CE: "Compilation Error",
  ERR: "Judge Unavailable",
};

const stripAnsi = (s: string) => s.replace(/\x1b\[[0-9;]*[A-Za-z]/g, "");
const lines = (a?: { text: string }[]) => (a ?? []).map((l) => l.text).join("\n");
const clip = (s: string) => (s.length > SHOW_LIMIT ? s.slice(0, SHOW_LIMIT) + "\n…" : s);

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

function Icon({ v }: { v: Verdict }) {
  if (v === "AC")
    return (
      <svg viewBox="0 0 16 16" className="size-4 shrink-0 text-easy" fill="currentColor" aria-hidden>
        <path d="M8 1a7 7 0 100 14A7 7 0 008 1zm3.3 5.2l-3.8 4.3a.75.75 0 01-1.1 0L4.7 8.8a.75.75 0 111.1-1l1.2 1.3 3.2-3.6a.75.75 0 111.1 1z" />
      </svg>
    );
  if (v === "running")
    return <span className="size-3.5 shrink-0 animate-spin rounded-full border-2 border-head border-t-transparent" />;
  if (v === "waiting" || v === "skipped") return <span className="size-3.5 shrink-0 rounded-full border-2 border-line" />;
  return (
    <svg viewBox="0 0 16 16" className={`size-4 shrink-0 ${v === "TLE" ? "text-medium" : "text-hard"}`} fill="currentColor" aria-hidden>
      <path d="M8 1a7 7 0 100 14A7 7 0 008 1zm2.5 8.4a.75.75 0 11-1.1 1.1L8 9.1l-1.4 1.4a.75.75 0 11-1.1-1.1L6.9 8 5.5 6.6a.75.75 0 111.1-1.1L8 6.9l1.4-1.4a.75.75 0 111.1 1.1L9.1 8l1.4 1.4z" />
    </svg>
  );
}

function Block({ title, children }: { title: string; children: React.ReactNode }) {
  return (
    <div>
      <p className="mb-1.5 text-[13px] font-bold text-fg">{title}</p>
      <pre className="max-h-48 overflow-auto rounded-md border border-line bg-[#f6f7f9] px-3 py-2 font-mono text-[13px] leading-relaxed whitespace-pre-wrap">
        {children}
      </pre>
    </div>
  );
}

export function Judge({ id }: { id: string }) {
  const key = `kdcp-code:${id}`;
  const [code, setCode] = useState(TEMPLATE);
  const [results, setResults] = useState<Result[] | null>(null);
  const [mode, setMode] = useState<"run" | "submit">("run");
  const [busy, setBusy] = useState(false);
  const [selected, setSelected] = useState(0);
  const [open, setOpen] = useState(false);
  const [panelH, setPanelH] = useState<number | null>(null); // results panel height in px (desktop); null = default
  const workspace = useRef<HTMLDivElement>(null);
  const panel = useRef<HTMLDivElement>(null);
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

  const fetchText = async (path: string) => {
    if (!cache.current.has(path)) {
      const r = await fetch(`${BASE}/judge/${path}`);
      if (!r.ok) throw new Error(`Could not load ${path}`);
      cache.current.set(path, await r.text());
    }
    return cache.current.get(path)!;
  };

  async function judge(which: "run" | "submit") {
    if (busy) return;
    setBusy(true);
    setMode(which);
    setSelected(0);
    setOpen(true);
    let tests: Test[];
    try {
      const manifest: Manifest = JSON.parse(await fetchText(`${id}/manifest.json`));
      tests = which === "run" ? manifest.tests.filter((t) => t.name.startsWith("Sample")) : manifest.tests;
    } catch {
      setResults([{ name: "Tests", verdict: "ERR", inputBytes: 0, message: "The tests for this problem could not be loaded." }]);
      setBusy(false);
      return;
    }
    const table: Result[] = tests.map((t) => ({ name: t.name, verdict: "waiting", inputBytes: t.bytes }));
    setResults([...table]);
    const update = (i: number, r: Partial<Result>) => {
      table[i] = { ...table[i], ...r };
      setResults([...table]);
    };

    let failed = false;
    for (let i = 0; i < tests.length && !failed; i++) {
      const t = tests[i];
      update(i, { verdict: "running" });
      setSelected(i);
      try {
        const stdin = await fetchText(`${id}/${t.input}`);
        const big = t.hash !== undefined;
        // Large outputs are hashed inside the program (wrapper_tail.cpp): the runner returns at most 32 KB.
        const source = big ? `${code}\n${await fetchText("wrapper_tail.cpp")}` : code;
        const r = await runOnCompilerExplorer(source, stdin);
        const ms = r.execTime ? Number(r.execTime) : undefined;
        const shown = { input: big ? undefined : clip(stdin), expected: big ? undefined : clip(t.output ?? "") };
        const out = lines(r.stdout);

        if (r.buildResult?.code) {
          update(i, { verdict: "CE", ms, message: stripAnsi(lines(r.buildResult.stderr)), ...shown });
          failed = true;
        } else if (r.timedOut || (ms ?? 0) > TIME_LIMIT_MS) {
          update(i, { verdict: "TLE", ms, message: `Your program ran longer than ${TIME_LIMIT_MS / 1000} seconds.`, ...shown });
          failed = true;
        } else if (r.code !== 0) {
          update(i, {
            verdict: "RE",
            ms,
            message: `Exit code ${r.code}\n${stripAnsi(lines(r.stderr))}`.trim(),
            got: big ? undefined : clip(out),
            ...shown,
          });
          failed = true;
        } else if (big) {
          const m = out.match(/KDCP (\d+) ([0-9a-f]{16})/);
          const ok = !!m && Number(m[1]) === t.count && m[2] === t.hash;
          update(i, {
            verdict: ok ? "AC" : "WA",
            ms,
            message: ok
              ? "Your output matches the expected output."
              : m && Number(m[1]) !== t.count
                ? `Expected ${t.count} tokens, got ${m[1]}.`
                : "Your output differs from the expected output. This test is too large to show the difference.",
          });
          failed = !ok;
        } else {
          const got = out.split(/\s+/).filter(Boolean);
          const exp = (t.output ?? "").split(/\s+/).filter(Boolean);
          const ok = !r.truncated && got.length === exp.length && got.every((g, k) => g === exp[k]);
          update(i, {
            verdict: ok ? "AC" : "WA",
            ms,
            got: clip(out),
            message: ok ? "Success" : r.truncated ? "Your program printed far more output than expected." : firstDiff(exp, got),
            ...shown,
          });
          failed = !ok;
        }
      } catch (e) {
        update(i, { verdict: "ERR", message: `Could not reach the runner: ${(e as Error).message}. Try again in a moment.` });
        failed = true;
      }
    }
    table.forEach((r, i) => r.verdict === "waiting" && update(i, { verdict: "skipped" }));
    setBusy(false);
  }

  const clampH = (h: number) => {
    const total = workspace.current?.clientHeight ?? 800;
    return Math.max(96, Math.min(h, total - 160)); // keep some editor visible
  };
  const startResize = (e: React.PointerEvent) => {
    e.preventDefault();
    const startY = e.clientY;
    const startH = panel.current?.offsetHeight ?? 300;
    const move = (ev: PointerEvent) => setPanelH(clampH(startH - (ev.clientY - startY)));
    const up = () => {
      window.removeEventListener("pointermove", move);
      window.removeEventListener("pointerup", up);
      document.body.style.cursor = "";
      document.body.style.userSelect = "";
    };
    document.body.style.cursor = "row-resize";
    document.body.style.userSelect = "none";
    window.addEventListener("pointermove", move);
    window.addEventListener("pointerup", up);
  };
  const resizeByKey = (e: React.KeyboardEvent) => {
    if (e.key !== "ArrowUp" && e.key !== "ArrowDown") return;
    e.preventDefault();
    const h = panel.current?.offsetHeight ?? 300;
    setPanelH(clampH(h + (e.key === "ArrowUp" ? 32 : -32)));
  };

  const done = !!results && !busy;
  const passed = results?.filter((r) => r.verdict === "AC").length ?? 0;
  const allPassed = done && passed === results!.length;
  const firstBad = results?.find((r) => !["AC", "skipped", "waiting"].includes(r.verdict));
  const current = results?.[selected];

  return (
    <div ref={workspace} className="flex min-h-0 flex-col bg-white lg:h-full">
      {/* toolbar */}
      <div className="flex items-center justify-between border-b border-line px-4 py-2">
        <span className="rounded-md border border-line px-2.5 py-1 text-[13px] font-medium">C++17</span>
        <div className="flex items-center gap-3 text-xs text-muted">
          <span className="hidden sm:inline">GCC 14 · -O2 · {TIME_LIMIT_MS / 1000} s</span>
          <button
            type="button"
            onClick={() => save(TEMPLATE)}
            disabled={busy}
            title="Reset to the starter code"
            className="rounded-md border border-line px-2.5 py-1 text-fg transition-colors hover:bg-soft"
          >
            Reset
          </button>
        </div>
      </div>

      {/* editor */}
      <CodeEditor
        value={code}
        onChange={save}
        onSubmit={() => judge("submit")}
        className="h-[26rem] border-b border-line lg:h-auto lg:flex-1"
      />

      {/* results */}
      {results && open && (
        <div
          role="separator"
          aria-orientation="horizontal"
          aria-label="Resize the results panel"
          tabIndex={0}
          onPointerDown={startResize}
          onKeyDown={resizeByKey}
          onDoubleClick={() => setPanelH(null)}
          title="Drag to resize · double-click to reset"
          className="hidden h-2.5 shrink-0 cursor-row-resize touch-none items-center justify-center border-b border-line bg-[#f3f5f7] outline-none transition-colors hover:bg-[#e8eef6] focus-visible:bg-[#e8eef6] lg:flex"
        >
          <span className="h-1 w-10 rounded-full bg-[#c2c7d0]" />
        </div>
      )}
      {results && open && (
        <div
          ref={panel}
          style={{ "--results-h": panelH ? `${panelH}px` : "45%" } as React.CSSProperties}
          className="shrink-0 overflow-auto border-b border-line px-4 pb-4 pt-3 lg:h-[var(--results-h)]"
        >
          <div className="flex items-start justify-between gap-3">
            {done ? (
              <div>
                <p className={`text-lg font-bold ${allPassed ? "text-easy" : "text-hard"}`}>
                  {allPassed
                    ? mode === "run"
                      ? "Congratulations! You passed the sample test cases."
                      : "Congratulations! You passed all test cases."
                    : LABEL[firstBad?.verdict ?? "WA"]}
                </p>
                <p className="mt-0.5 text-[13px] text-muted">
                  {passed}/{results.length} test cases passed
                  {allPassed && mode === "run" ? ". Click Submit Code to run all tests." : ""}
                </p>
              </div>
            ) : (
              <p className="py-1 text-sm font-bold text-muted">
                {mode === "run" ? "Running the sample test cases…" : "Judging all test cases…"}
              </p>
            )}
            <button
              type="button"
              onClick={() => setOpen(false)}
              aria-label="Close results"
              title="Close"
              className="grid size-8 shrink-0 place-items-center rounded-md text-muted transition-colors hover:bg-soft hover:text-fg"
            >
              <svg viewBox="0 0 16 16" className="size-4" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" aria-hidden>
                <path d="M4 4l8 8M12 4l-8 8" />
              </svg>
            </button>
          </div>

          {/* test cases as tabs in one row */}
          <div role="tablist" className="mt-3 flex flex-wrap gap-x-1 border-b border-line">
            {results.map((r, i) => (
              <button
                key={r.name}
                type="button"
                role="tab"
                aria-selected={i === selected}
                onClick={() => setSelected(i)}
                className={`-mb-px flex items-center gap-1.5 whitespace-nowrap border-b-2 px-3 py-2 text-[13px] transition-colors ${
                  i === selected ? "border-[#1ba94c] font-bold text-fg" : "border-transparent text-muted hover:text-fg"
                }`}
              >
                <Icon v={r.verdict} />
                {r.name}
              </button>
            ))}
          </div>

          {current && (
            <div className="mt-4 space-y-3">
              <Block title="Compiler Message">
                {current.verdict === "waiting" || current.verdict === "running"
                  ? LABEL[current.verdict] + "…"
                  : current.verdict === "skipped"
                    ? "Not run, because an earlier test case failed."
                    : `${current.verdict === "AC" ? "" : LABEL[current.verdict] + "\n"}${current.message ?? ""}`.trim()}
                {current.ms !== undefined ? `\n(${current.ms} ms)` : ""}
              </Block>
              {current.input !== undefined ? (
                <Block title="Input (stdin)">{current.input}</Block>
              ) : (
                current.inputBytes > 0 && (
                  <p className="text-[13px] text-muted">Input is {(current.inputBytes / 1e6).toFixed(1)} MB, too large to show.</p>
                )
              )}
              {current.got !== undefined && <Block title="Your Output (stdout)">{current.got || " "}</Block>}
              {current.expected !== undefined && <Block title="Expected Output">{current.expected}</Block>}
            </div>
          )}
        </div>
      )}

      {/* actions */}
      <div className="flex shrink-0 items-center justify-between gap-3 px-4 py-3">
        {results && !open ? (
          <button type="button" onClick={() => setOpen(true)} className="text-xs font-bold text-link hover:underline">
            Show results ({passed}/{results.length})
          </button>
        ) : (
          <span className="hidden text-xs text-muted sm:inline">Runs on godbolt.org (Compiler Explorer)</span>
        )}
        <div className="ml-auto flex gap-2">
          <button
            type="button"
            onClick={() => judge("run")}
            disabled={busy}
            className="rounded-md border border-[#c2c7d0] bg-white px-4 py-2 text-sm font-bold text-fg transition-colors hover:bg-soft disabled:opacity-60"
          >
            {busy && mode === "run" ? "Running…" : "Run Code"}
          </button>
          <button
            type="button"
            onClick={() => judge("submit")}
            disabled={busy}
            className="rounded-md bg-[#1ba94c] px-4 py-2 text-sm font-bold text-white transition-colors hover:bg-[#178f41] disabled:opacity-60"
          >
            {busy && mode === "submit" ? "Judging…" : "Submit Code"}
          </button>
        </div>
      </div>
    </div>
  );
}
