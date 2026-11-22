#!/usr/bin/env python3
"""KDCP local judge for the extra practice problems.

Usage
  python3 judge/judge.py --list                     list problems
  python3 judge/judge.py <problem> my.cpp           judge your solution
  python3 judge/judge.py <problem> my.cpp -n 50     more random tests
  python3 judge/judge.py <problem> --stress         check sol.cpp against brute.cpp

Each problem folder in judge/problems/<problem>/ holds:
  statement.md   the statement, with sample input/output
  sol.cpp        reference solution (produces the expected answers)
  gen.cpp        test generator:  ./gen <seed> <small|large>
  brute.cpp      slow but obviously-correct solution (used by --stress)

Your program reads stdin and writes stdout. Output is compared token by token
(extra spaces and newlines are ignored), like the "tokens" checker on TopAlgo.
"""
from __future__ import annotations

import argparse
import hashlib
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PROBLEMS = ROOT / "problems"
BUILD = ROOT / ".build"
CXX = os.environ.get("CXX", "g++")
CXXFLAGS = ["-std=c++17", "-O2", "-pipe"]

GREEN, RED, YELLOW, DIM, BOLD, RESET = (
    ("\033[32m", "\033[31m", "\033[33m", "\033[2m", "\033[1m", "\033[0m")
    if sys.stdout.isatty()
    else ("",) * 6
)


def die(msg: str) -> None:
    print(f"{RED}error:{RESET} {msg}", file=sys.stderr)
    sys.exit(2)


def compile_cpp(src: Path, tag: str) -> Path:
    """Compile src into .build/, reusing the binary while the source is unchanged."""
    if not src.exists():
        die(f"{src} not found")
    BUILD.mkdir(exist_ok=True)
    digest = hashlib.sha1(src.read_bytes() + " ".join([CXX, *CXXFLAGS]).encode()).hexdigest()[:12]
    exe = BUILD / f"{tag}-{digest}"
    if not exe.exists():
        r = subprocess.run([CXX, *CXXFLAGS, str(src), "-o", str(exe)], capture_output=True, text=True)
        if r.returncode != 0:
            print(f"{RED}Compilation error{RESET} in {src}:\n{r.stderr[:4000]}")
            sys.exit(1)
    return exe


def run(exe: Path, stdin: str, timeout: float) -> tuple[str, str, float]:
    """Returns (status, stdout, seconds). status is OK, TLE or RE."""
    start = time.perf_counter()
    try:
        r = subprocess.run([str(exe)], input=stdin, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return "TLE", "", timeout
    took = time.perf_counter() - start
    if r.returncode != 0:
        return "RE", r.stdout + r.stderr[-500:], took
    return "OK", r.stdout, took


def first_diff(expected: list[str], got: list[str]) -> str:
    for i, (e, g) in enumerate(zip(expected, got)):
        if e != g:
            return f"token #{i + 1}: expected {e!r}, got {g!r}"
    if len(expected) != len(got):
        return f"expected {len(expected)} tokens, got {len(got)}"
    return ""


def samples(problem: Path) -> list[tuple[str, str]]:
    """Sample pairs from statement.md: ```input / ```output fenced blocks, in order."""
    text = (problem / "statement.md").read_text()
    ins = re.findall(r"```input\n(.*?)```", text, re.S)
    outs = re.findall(r"```output\n(.*?)```", text, re.S)
    return list(zip(ins, outs))


def title_of(problem: Path) -> str:
    m = re.search(r"^title:\s*(.+)$", (problem / "statement.md").read_text(), re.M)
    return m.group(1).strip() if m else problem.name


def make_tests(problem: Path, n_random: int, small_only: bool = False) -> list[tuple[str, str]]:
    """(name, input) pairs: samples, then small random, then large random."""
    gen = compile_cpp(problem / "gen.cpp", f"{problem.name}-gen")
    tests = [(f"sample {i + 1}", inp) for i, (inp, _) in enumerate(samples(problem))]
    n_large = 0 if small_only else max(2, n_random // 4)
    for i in range(n_random):
        size = "large" if i >= n_random - n_large else "small"
        r = subprocess.run([str(gen), str(1000 + i), size], capture_output=True, text=True)
        if r.returncode != 0:
            die(f"generator failed: {r.stderr[:500]}")
        tests.append((f"{size} #{i + 1}", r.stdout))
    return tests


def judge(problem: Path, candidate: Path, reference: Path, n_random: int, timeout: float, label: str, small_only: bool = False) -> bool:
    ref = compile_cpp(reference, f"{problem.name}-{reference.stem}")
    you = compile_cpp(candidate, f"{problem.name}-you-{candidate.stem}")
    print(f"{BOLD}{title_of(problem)}{RESET}  {DIM}({problem.name}, {label}){RESET}")

    # Samples must match the statement exactly, which also checks the reference.
    for i, (inp, out) in enumerate(samples(problem)):
        st, got, _ = run(ref, inp, 10)
        if st != "OK" or got.split() != out.split():
            die(f"reference does not match sample {i + 1} in statement.md")

    passed = 0
    tests = make_tests(problem, n_random, small_only)
    for name, inp in tests:
        st, expected, _ = run(ref, inp, 30)
        if st != "OK":
            die(f"reference failed ({st}) on {name}")
        st, got, took = run(you, inp, timeout)
        if st == "OK":
            diff = first_diff(expected.split(), got.split())
            st = "WA" if diff else "AC"
        else:
            diff = got.strip()[-300:] if st == "RE" else f"over {timeout:g}s"
        color = GREEN if st == "AC" else (YELLOW if st == "TLE" else RED)
        print(f"  {name:<12} {color}{st:<3}{RESET} {DIM}{took * 1000:6.0f} ms{RESET}  {diff}")
        if st == "AC":
            passed += 1
        else:
            failed = BUILD / f"failed-{problem.name}.txt"
            failed.write_text(inp)
            print(f"\n  The failing input was saved to {failed.relative_to(Path.cwd()) if failed.is_relative_to(Path.cwd()) else failed}")
            break
    ok = passed == len(tests)
    verdict = f"{GREEN}ACCEPTED{RESET}" if ok else f"{RED}FAILED{RESET}"
    print(f"\n{verdict}  {passed}/{len(tests)} tests passed")
    return ok


def main() -> None:
    ap = argparse.ArgumentParser(description="KDCP local judge for C++ solutions")
    ap.add_argument("problem", nargs="?", help="problem id, e.g. s1-even-numbers")
    ap.add_argument("solution", nargs="?", type=Path, help="your .cpp file")
    ap.add_argument("-n", "--tests", type=int, default=20, help="number of random tests (default 20)")
    ap.add_argument("-t", "--time", type=float, default=3.0, help="time limit per test in seconds (default 3)")
    ap.add_argument("--list", action="store_true", help="list problems")
    ap.add_argument("--stress", action="store_true", help="compare sol.cpp with brute.cpp on small tests")
    ap.add_argument("--clean", action="store_true", help="delete compiled binaries")
    a = ap.parse_args()

    if not shutil.which(CXX):
        die(f"C++ compiler '{CXX}' not found (set CXX=clang++ to use another)")
    if a.clean:
        shutil.rmtree(BUILD, ignore_errors=True)
        print("removed", BUILD)
        return
    ids = sorted(p.name for p in PROBLEMS.iterdir() if (p / "statement.md").exists())
    if a.list or not a.problem:
        for pid in ids:
            print(f"  {pid:<32} {title_of(PROBLEMS / pid)}")
        return
    if a.problem not in ids:
        close = [p for p in ids if a.problem in p]
        die(f"unknown problem '{a.problem}'" + (f"; did you mean {', '.join(close)}?" if close else ""))
    problem = PROBLEMS / a.problem

    if a.stress:
        # brute.cpp plays the contestant: it must agree with sol.cpp on small tests.
        ok = judge(problem, problem / "brute.cpp", problem / "sol.cpp", a.tests, 10.0, "stress: brute vs sol", small_only=True)
        sys.exit(0 if ok else 1)
    if not a.solution:
        die("give the path to your .cpp file")
    ok = judge(problem, a.solution, problem / "sol.cpp", a.tests, a.time, f"limit {a.time:g}s")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
