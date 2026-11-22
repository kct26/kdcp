"use client";
import { useEffect, useRef, useState } from "react";
import { CodeEditor } from "./CodeEditor";

/* LeetCode-style code + test panels. Run (sample cases) and Submit (all cases) compile and run
   the code on Compiler Explorer (godbolt.org) against tests generated at build time by
   judge/web/build_tests.py. */

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
const SHOW_LIMIT = 6000; // characters of input/output shown per case
const HEADER_PX = 41; // height of a panel header
const TEMPLATE = `#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}
`;

const LABEL: Record<Verdict, string> = {
  waiting: "Pending",
  skipped: "Not run",
  running: "Running",
  AC: "Accepted",
  WA: "Wrong Answer",
  TLE: "Time Limit Exceeded",
  RE: "Runtime Error",
  CE: "Compile Error",
  ERR: "Judge Unavailable",
};

const stripAnsi = (s: string) => s.replace(/\x1b\[[0-9;]*[A-Za-z]/g, "");
const lines = (a?: { text: string }[]) => (a ?? []).map((l) => l.text).join("\n");
const clip = (s: string) => (s.length > SHOW_LIMIT ? s.slice(0, SHOW_LIMIT) + "\n…" : s);
const caseName = (name: string, i: number, all: { name: string }[]) =>
  all.every((t) => t.name.startsWith("Sample")) ? `Case ${i + 1}` : name;

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

/* ---------- small pieces ---------- */

function CaseIcon({ v }: { v: Verdict }) {
  if (v === "AC")
    return (
      <svg viewBox="0 0 16 16" className="size-3.5 shrink-0" aria-hidden>
        <rect width="16" height="16" rx="3" fill="#2cbb5d" />
        <path d="M4.5 8.3l2.3 2.2 4.7-5" fill="none" stroke="#fff" strokeWidth="1.8" strokeLinecap="round" strokeLinejoin="round" />
      </svg>
    );
  if (v === "running") return <span className="size-3.5 shrink-0 animate-spin rounded-full border-2 border-[#1a90ff] border-t-transparent" />;
  if (v === "waiting" || v === "skipped") return <span className="size-3.5 shrink-0 rounded-[3px] border-2 border-[#d0d0d0]" />;
  return (
    <svg viewBox="0 0 16 16" className="size-3.5 shrink-0" aria-hidden>
      <rect width="16" height="16" rx="3" fill={v === "TLE" ? "#ffa116" : "#ef4743"} />
      <path d="M5.2 5.2l5.6 5.6M10.8 5.2l-5.6 5.6" stroke="#fff" strokeWidth="1.8" strokeLinecap="round" />
    </svg>
  );
}

function Field({ label, children, tone }: { label: string; children: React.ReactNode; tone?: "error" }) {
  return (
    <div>
      <p className="mb-2 text-xs font-medium text-[#8c8c8c]">{label}</p>
      <pre
        className={`max-h-56 overflow-auto rounded-lg px-4 py-3 font-mono text-[13px] leading-relaxed whitespace-pre-wrap ${
          tone === "error" ? "bg-[#fdeceb] text-[#c42b27]" : "bg-[#f7f7f8] text-fg"
        }`}
      >
        {children}
      </pre>
    </div>
  );
}

function Pills({
  items,
  selected,
  onSelect,
  icons,
}: {
  items: { name: string; verdict?: Verdict }[];
  selected: number;
  onSelect: (i: number) => void;
  icons: boolean;
}) {
  return (
    <div role="tablist" className="flex flex-wrap gap-2">
      {items.map((it, i) => (
        <button
          key={it.name}
          type="button"
          role="tab"
          aria-selected={i === selected}
          onClick={() => onSelect(i)}
          className={`flex items-center gap-2 rounded-lg px-4 py-1.5 text-[13px] font-medium transition-colors ${
            i === selected ? "bg-[#ebebeb] text-fg" : "text-[#8c8c8c] hover:bg-[#f5f5f5] hover:text-fg"
          }`}
        >
          {icons && it.verdict && <CaseIcon v={it.verdict} />}
          {caseName(it.name, i, items)}
        </button>
      ))}
    </div>
  );
}

function PanelTab({ active, onClick, icon, children }: { active: boolean; onClick: () => void; icon: React.ReactNode; children: React.ReactNode }) {
  return (
    <button
      type="button"
      onClick={onClick}
      className={`flex items-center gap-1.5 rounded-md px-2 py-1 text-[13px] transition-colors hover:bg-[#ebebeb] ${
        active ? "font-bold text-fg" : "text-[#8c8c8c]"
      }`}
    >
      {icon}
      {children}
    </button>
  );
}

/* ---------- main ---------- */

export function Judge({ id }: { id: string }) {
  const key = `kdcp-code:${id}`;
  const [code, setCode] = useState(TEMPLATE);
  const [samples, setSamples] = useState<{ name: string; input: string }[]>([]);
  const [results, setResults] = useState<Result[] | null>(null);
  const [mode, setMode] = useState<"run" | "submit">("run");
  const [busy, setBusy] = useState(false);
  const [tab, setTab] = useState<"testcase" | "result">("testcase");
  const [sampleSel, setSampleSel] = useState(0);
  const [resultSel, setResultSel] = useState(0);
  const [testsH, setTestsH] = useState<number | null>(null); // bottom panel height in px; null = default
  const [collapsed, setCollapsed] = useState(false);
  const [dragging, setDragging] = useState(false);
  const column = useRef<HTMLDivElement>(null);
  const bottom = useRef<HTMLDivElement>(null);
  const cache = useRef(new Map<string, string>());

  const fetchText = async (path: string) => {
    if (!cache.current.has(path)) {
      const r = await fetch(`${BASE}/judge/${path}`);
      if (!r.ok) throw new Error(`Could not load ${path}`);
      cache.current.set(path, await r.text());
    }
    return cache.current.get(path)!;
  };

  useEffect(() => {
    try {
      const saved = localStorage.getItem(key);
      if (saved) setCode(saved);
      const h = Number(localStorage.getItem("kdcp-split-tests"));
      if (h >= 41) setTestsH(h);
    } catch {}
    // show the sample inputs in the Testcase tab
    (async () => {
      try {
        const m: Manifest = JSON.parse(await fetchText(`${id}/manifest.json`));
        const s = m.tests.filter((t) => t.name.startsWith("Sample"));
        setSamples(await Promise.all(s.map(async (t) => ({ name: t.name, input: await fetchText(`${id}/${t.input}`) }))));
      } catch {}
    })();
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [id]);

  const save = (v: string) => {
    setCode(v);
    try {
      localStorage.setItem(key, v);
    } catch {}
  };

  /* ---- resizing the code / tests split ---- */
  const clampH = (h: number) => Math.max(HEADER_PX, Math.min(h, (column.current?.clientHeight ?? 800) - 140));
  const setHeight = (h: number | null) => {
    setTestsH(h);
    setCollapsed(false);
    try {
      if (h === null) localStorage.removeItem("kdcp-split-tests");
      else localStorage.setItem("kdcp-split-tests", String(h));
    } catch {}
  };
  const startResize = (e: React.PointerEvent) => {
    e.preventDefault();
    setDragging(true);
    const startY = e.clientY;
    const startH = bottom.current?.offsetHeight ?? 300;
    const move = (ev: PointerEvent) => setHeight(clampH(startH - (ev.clientY - startY)));
    const up = () => {
      setDragging(false);
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

  /* ---- judging ---- */
  async function judge(which: "run" | "submit") {
    if (busy) return;
    setBusy(true);
    setMode(which);
    setResultSel(0);
    setTab("result");
    setCollapsed(false);
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
              ? undefined
              : m && Number(m[1]) !== t.count
                ? `Expected ${t.count} tokens, got ${m[1]}.`
                : "Your output differs from the expected output. This case is too large to show the difference.",
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
            message: ok ? undefined : r.truncated ? "Your program printed far more output than expected." : firstDiff(exp, got),
            ...shown,
          });
          failed = !ok;
        }
        if (failed) setResultSel(i);
      } catch (e) {
        update(i, { verdict: "ERR", message: `Could not reach the runner: ${(e as Error).message}. Try again in a moment.` });
        failed = true;
        setResultSel(i);
      }
    }
    table.forEach((r, i) => r.verdict === "waiting" && update(i, { verdict: "skipped" }));
    setBusy(false);
  }

  const done = !!results && !busy;
  const passed = results?.filter((r) => r.verdict === "AC").length ?? 0;
  const allPassed = done && passed === results!.length;
  const firstBad = results?.find((r) => !["AC", "skipped", "waiting"].includes(r.verdict));
  const runtime = results ? Math.max(0, ...results.map((r) => r.ms ?? 0)) : 0;
  const current = results?.[resultSel];

  const bottomStyle = {
    "--tests-h": collapsed ? `${HEADER_PX}px` : testsH ? `${testsH}px` : "42%",
  } as React.CSSProperties;

  return (
    <div ref={column} className="flex min-h-0 flex-1 flex-col gap-2 lg:gap-0">
      {/* ---------- Code card ---------- */}
      <section className="flex min-h-0 flex-col overflow-hidden rounded-lg border border-[#e5e5e5] bg-white lg:flex-1">
        <div className="flex h-[41px] shrink-0 items-center justify-between gap-2 border-b border-[#eee] bg-[#fafafa] px-3">
          <div className="flex items-center gap-3">
            <span className="flex items-center gap-1.5 text-[13px] font-bold">
              <svg viewBox="0 0 16 16" className="size-4 text-[#2cbb5d]" fill="none" stroke="currentColor" strokeWidth="1.8" strokeLinecap="round" strokeLinejoin="round" aria-hidden>
                <path d="M5.5 4.5L2 8l3.5 3.5M10.5 4.5L14 8l-3.5 3.5M9 3l-2 10" />
              </svg>
              Code
            </span>
            <span className="text-[13px] text-[#8c8c8c]" title="GCC 14 · -O2 · 3 s per test">
              C++17
            </span>
          </div>
          <div className="flex items-center gap-2">
            <button
              type="button"
              onClick={() => save(TEMPLATE)}
              disabled={busy}
              title="Reset to the starter code"
              className="rounded-md px-2 py-1 text-[13px] text-[#8c8c8c] transition-colors hover:bg-[#ebebeb] hover:text-fg"
            >
              Reset
            </button>
            <button
              type="button"
              onClick={() => judge("run")}
              disabled={busy}
              title="Run the sample cases"
              className="flex items-center gap-1.5 rounded-md bg-[#ebebeb] px-3 py-1 text-[13px] font-medium text-fg transition-colors hover:bg-[#e0e0e0] disabled:opacity-60"
            >
              <svg viewBox="0 0 16 16" className="size-3" fill="currentColor" aria-hidden>
                <path d="M4 2.8v10.4a.6.6 0 00.9.5l8.3-5.2a.6.6 0 000-1L4.9 2.3a.6.6 0 00-.9.5z" />
              </svg>
              {busy && mode === "run" ? "Running…" : "Run"}
            </button>
            <button
              type="button"
              onClick={() => judge("submit")}
              disabled={busy}
              title="Submit (Cmd/Ctrl + Enter)"
              className="flex items-center gap-1.5 rounded-md bg-[#2cbb5d] px-3 py-1 text-[13px] font-bold text-white transition-colors hover:bg-[#25a551] disabled:opacity-60"
            >
              <svg viewBox="0 0 16 16" className="size-3.5" fill="none" stroke="currentColor" strokeWidth="1.8" strokeLinecap="round" strokeLinejoin="round" aria-hidden>
                <path d="M8 11V3M4.5 6.5L8 3l3.5 3.5M3 13h10" />
              </svg>
              {busy && mode === "submit" ? "Judging…" : "Submit"}
            </button>
          </div>
        </div>
        <CodeEditor value={code} onChange={save} onSubmit={() => judge("submit")} className="h-[24rem] lg:h-auto lg:flex-1" />
      </section>

      {/* ---------- divider ---------- */}
      <div
        role="separator"
        aria-orientation="horizontal"
        aria-label="Resize the code and test panels"
        tabIndex={0}
        onPointerDown={startResize}
        onDoubleClick={() => setHeight(null)}
        onKeyDown={(e) => {
          if (e.key !== "ArrowUp" && e.key !== "ArrowDown") return;
          e.preventDefault();
          setHeight(clampH((bottom.current?.offsetHeight ?? 300) + (e.key === "ArrowUp" ? 32 : -32)));
        }}
        title="Drag to resize · double-click to reset"
        className="group hidden h-2 shrink-0 cursor-row-resize touch-none items-center outline-none lg:flex"
      >
        <span
          className={`mx-1 h-[3px] w-full rounded-full transition-colors group-hover:bg-[#1a90ff] group-focus-visible:bg-[#1a90ff] ${
            dragging ? "bg-[#1a90ff]" : "bg-transparent"
          }`}
        />
      </div>

      {/* ---------- Testcase / Test Result card ---------- */}
      <section
        ref={bottom}
        style={bottomStyle}
        className="flex min-h-0 shrink-0 flex-col overflow-hidden rounded-lg border border-[#e5e5e5] bg-white lg:h-[var(--tests-h)]"
      >
        <div className="flex h-[41px] shrink-0 items-center justify-between border-b border-[#eee] bg-[#fafafa] px-2">
          <div className="flex items-center gap-1">
            <PanelTab
              active={tab === "testcase"}
              onClick={() => (setTab("testcase"), setCollapsed(false))}
              icon={
                <svg viewBox="0 0 16 16" className="size-4 text-[#2cbb5d]" fill="none" stroke="currentColor" strokeWidth="1.6" aria-hidden>
                  <rect x="2.5" y="2.5" width="11" height="11" rx="2" />
                  <path d="M5.5 8.2l1.7 1.6 3.3-3.6" strokeLinecap="round" strokeLinejoin="round" />
                </svg>
              }
            >
              Testcase
            </PanelTab>
            <span className="h-4 w-px bg-[#e0e0e0]" />
            <PanelTab
              active={tab === "result"}
              onClick={() => (setTab("result"), setCollapsed(false))}
              icon={
                <svg viewBox="0 0 16 16" className="size-4 text-[#2cbb5d]" fill="none" stroke="currentColor" strokeWidth="1.8" strokeLinecap="round" strokeLinejoin="round" aria-hidden>
                  <path d="M2.5 4l4 4-4 4M8 12.5h5.5" />
                </svg>
              }
            >
              Test Result
            </PanelTab>
          </div>
          <button
            type="button"
            onClick={() => setCollapsed(!collapsed)}
            aria-label={collapsed ? "Expand the test panel" : "Collapse the test panel"}
            title={collapsed ? "Expand" : "Collapse"}
            className="grid size-7 place-items-center rounded-md text-[#8c8c8c] transition-colors hover:bg-[#ebebeb] hover:text-fg"
          >
            <svg viewBox="0 0 16 16" className={`size-4 transition-transform ${collapsed ? "rotate-180" : ""}`} fill="none" stroke="currentColor" strokeWidth="1.8" strokeLinecap="round" strokeLinejoin="round" aria-hidden>
              <path d="M4 6l4 4 4-4" />
            </svg>
          </button>
        </div>

        {!collapsed && (
          <div className="min-h-0 flex-1 overflow-auto px-5 py-4">
            {tab === "testcase" ? (
              samples.length === 0 ? (
                <p className="text-[13px] text-[#8c8c8c]">Loading test cases…</p>
              ) : (
                <div className="space-y-4">
                  <Pills items={samples} selected={sampleSel} onSelect={setSampleSel} icons={false} />
                  <Field label="Input">{samples[sampleSel]?.input}</Field>
                </div>
              )
            ) : !results ? (
              <p className="pt-6 text-center text-[13px] text-[#8c8c8c]">You must run your code first.</p>
            ) : (
              <div className="space-y-4">
                <div className="flex flex-wrap items-baseline gap-x-4 gap-y-1">
                  {done ? (
                    <>
                      <h3 className={`text-2xl font-bold ${allPassed ? "text-[#2cbb5d]" : "text-[#ef4743]"}`}>
                        {allPassed ? "Accepted" : LABEL[firstBad?.verdict ?? "WA"]}
                      </h3>
                      <span className="text-[13px] text-[#8c8c8c]">Runtime: {runtime} ms</span>
                      {mode === "submit" && (
                        <span className="text-[13px] text-[#8c8c8c]">
                          {passed} / {results.length} testcases passed
                        </span>
                      )}
                    </>
                  ) : (
                    <h3 className="text-lg font-bold text-[#8c8c8c]">
                      {mode === "run" ? "Running…" : "Judging…"} {passed}/{results.length}
                    </h3>
                  )}
                </div>

                <Pills items={results} selected={resultSel} onSelect={setResultSel} icons />

                {current && (
                  <div className="space-y-4">
                    {current.message && ["CE", "RE", "TLE", "ERR"].includes(current.verdict) && (
                      <Field label={LABEL[current.verdict]} tone="error">
                        {current.message}
                      </Field>
                    )}
                    {current.verdict === "skipped" && <p className="text-[13px] text-[#8c8c8c]">Not run, because an earlier case failed.</p>}
                    {current.input !== undefined ? (
                      <Field label="Input">{current.input}</Field>
                    ) : (
                      current.inputBytes > 0 &&
                      current.verdict !== "skipped" && (
                        <p className="text-[13px] text-[#8c8c8c]">
                          Input is {(current.inputBytes / 1e6).toFixed(1)} MB, too large to show.
                          {current.verdict === "AC" ? " Your output matches the expected output." : ""}
                        </p>
                      )
                    )}
                    {current.got !== undefined && <Field label="Output">{current.got || " "}</Field>}
                    {current.expected !== undefined && <Field label="Expected">{current.expected}</Field>}
                    {current.verdict === "WA" && current.message && (
                      <p className="text-[13px] text-[#ef4743]">{current.message}</p>
                    )}
                  </div>
                )}
              </div>
            )}
          </div>
        )}
      </section>
    </div>
  );
}
