#!/usr/bin/env python3
"""Build the test data the website judge uses.

For every problem in judge/problems it writes public/judge/<id>/:
  manifest.json   the test list; small tests carry the full expected output,
                  large ones only a token count and an FNV-1a 64 checksum
  NN.in           test inputs
It also copies wrapper_tail.cpp (the output-checksum wrapper) to public/judge/.

Runs in CI before `next build`; run it locally before `npm run dev` to try the judge.
"""
from __future__ import annotations

import json
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
import judge as J  # noqa: E402  (reuses compile/run helpers)

OUT = HERE.parent.parent / "public" / "judge"
SMALL, LARGE = 6, 3
MAX_INPUT = 7_000_000          # the runner rejects requests above ~8 MB


def fnv(text: str) -> tuple[int, str]:
    h, tokens = 1469598103934665603, text.split()
    for i, tok in enumerate(tokens):
        if i:
            h = ((h ^ 32) * 1099511628211) % 2**64
        for b in tok.encode():
            h = ((h ^ b) * 1099511628211) % 2**64
    return len(tokens), f"{h:016x}"


def build(problem: Path) -> dict:
    gen = J.compile_cpp(problem / "gen.cpp", f"{problem.name}-gen")
    sol = J.compile_cpp(problem / "sol.cpp", f"{problem.name}-sol")
    dest = OUT / problem.name
    dest.mkdir(parents=True, exist_ok=True)

    inputs: list[tuple[str, str, bool]] = [(f"Sample {i + 1}", inp, False) for i, (inp, _) in enumerate(J.samples(problem))]
    for i in range(SMALL + LARGE):
        size = "large" if i >= SMALL else "small"
        seed = 7000 + i
        r = subprocess.run([str(gen), str(seed), size], capture_output=True, text=True, check=True)
        if len(r.stdout) > MAX_INPUT:
            print(f"  {problem.name}: skipping a {len(r.stdout) / 1e6:.1f} MB test (too big for the runner)")
            continue
        inputs.append((f"{size.capitalize()} {i + 1 - (SMALL if size == 'large' else 0)}", r.stdout, size == "large"))

    tests = []
    for k, (name, inp, big) in enumerate(inputs):
        status, out, _ = J.run(sol, inp, 60)
        if status != "OK":
            J.die(f"reference failed on {problem.name} {name}")
        file = f"{k:02d}.in"
        (dest / file).write_text(inp)
        t = {"name": name, "input": file, "bytes": len(inp)}
        if big:
            t["count"], t["hash"] = fnv(out)
        else:
            t["output"] = out
        tests.append(t)
    manifest = {"id": problem.name, "title": J.title_of(problem), "tests": tests}
    (dest / "manifest.json").write_text(json.dumps(manifest))
    return manifest


def main() -> None:
    shutil.rmtree(OUT, ignore_errors=True)
    OUT.mkdir(parents=True)
    shutil.copy(HERE / "wrapper_tail.cpp", OUT / "wrapper_tail.cpp")
    total = 0
    for problem in sorted(p for p in J.PROBLEMS.iterdir() if (p / "statement.md").exists()):
        m = build(problem)
        size = sum(t["bytes"] for t in m["tests"])
        total += size
        print(f"  {problem.name:<28} {len(m['tests'])} tests  {size / 1e6:5.1f} MB")
    print(f"web judge tests written to {OUT} ({total / 1e6:.0f} MB)")


if __name__ == "__main__":
    main()
