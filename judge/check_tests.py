#!/usr/bin/env python3
"""Check that the website tests are strong enough.

For every problem it runs, against the exact tests in public/judge/<id>/ (built by
judge/web/build_tests.py):
  * sol.cpp, solution.cpp and every
    judge/mutants/<id>/ok-*.cpp                     -> must pass every test
  * every judge/mutants/<id>/bad-*.cpp              -> must fail at least one test
  * every edit listed in judge/mutants/<id>/mutants.json, applied to sol.cpp
                                                    -> must fail at least one test
  * brute.cpp (slow but correct)                    -> must fail (too slow on the large tests),
                                                       unless mutants.json sets "brute_is_fast": true
A wrong solution that passes everything means the tests need to be stronger.

  python3 judge/web/build_tests.py && python3 judge/check_tests.py [problem ...]
"""
from __future__ import annotations

import json
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import judge as J  # noqa: E402

TESTS = HERE.parent / "public" / "judge"
MUTANTS = HERE / "mutants"
TIME_LIMIT = 3.0


def fnv(text: str) -> tuple[int, str]:
    h, tokens = 1469598103934665603, text.split()
    for i, tok in enumerate(tokens):
        if i:
            h = ((h ^ 32) * 1099511628211) % 2**64
        for b in tok.encode():
            h = ((h ^ b) * 1099511628211) % 2**64
    return len(tokens), f"{h:016x}"


def judge_all(exe: Path, pid: str, tests: list[dict]) -> tuple[bool, str]:
    """Returns (passed_everything, description of the first failure)."""
    for t in tests:
        inp = (TESTS / pid / t["input"]).read_text()
        status, out, _ = J.run(exe, inp, TIME_LIMIT)
        if status == "OK":
            if "hash" in t:
                ok = fnv(out) == (t["count"], t["hash"])
            else:
                ok = out.split() == t["output"].split()
            status = "AC" if ok else "WA"
        if status != "AC":
            return False, f"{status} on {t['name']}"
    return True, ""


def programs(pid: str) -> list[tuple[str, str, bool]]:
    """(label, source code, must_pass)."""
    prob = J.PROBLEMS / pid
    sol = (prob / "sol.cpp").read_text()
    out = [("sol.cpp", sol, True)]
    mdir = MUTANTS / pid
    spec = json.loads((mdir / "mutants.json").read_text()) if (mdir / "mutants.json").exists() else {}
    if (prob / "solution.cpp").exists():
        out.append(("solution.cpp", (prob / "solution.cpp").read_text(), True))
    for f in sorted(mdir.glob("ok-*.cpp")) if mdir.exists() else []:
        out.append((f.name, f.read_text(), True))
    if (prob / "brute.cpp").exists() and not spec.get("brute_is_fast"):
        out.append(("brute.cpp (too slow)", (prob / "brute.cpp").read_text(), False))
    for f in sorted(mdir.glob("bad-*.cpp")) if mdir.exists() else []:
        out.append((f.name, f.read_text(), False))
    for m in spec.get("mutants", []):
        src = sol
        for old, new in m["edits"]:
            if old not in src:
                J.die(f"{pid}: mutant '{m['name']}' edit not found in sol.cpp: {old!r}")
            src = src.replace(old, new, 1)
        out.append((m["name"], src, False))
    return out


def main() -> None:
    args = [a for a in sys.argv[1:] if not a.startswith("-")]
    ids = args or sorted(p.name for p in J.PROBLEMS.iterdir() if (p / "statement.md").exists())
    build = J.BUILD / "mutants"
    build.mkdir(parents=True, exist_ok=True)
    problems_ok = True
    for pid in ids:
        tests = json.loads((TESTS / pid / "manifest.json").read_text())["tests"]
        lines, bad = [], False
        for label, src, must_pass in programs(pid):
            path = build / f"{pid}--{label.split()[0].replace('.cpp', '')}.cpp"
            path.write_text(src)
            exe = J.compile_cpp(path, f"mut-{pid}-{path.stem}")
            passed, why = judge_all(exe, pid, tests)
            if must_pass and not passed:
                lines.append(f"    {J.RED}FAILS{J.RESET}   {label}: {why}  (a correct solution must pass)")
                bad = True
            elif not must_pass and passed:
                lines.append(f"    {J.RED}SURVIVES{J.RESET} {label}  (wrong solution passes every test)")
                bad = True
            else:
                lines.append(f"    {J.DIM}ok       {label}: {'passes' if must_pass else 'caught, ' + why}{J.RESET}")
        mark = f"{J.RED}✗{J.RESET}" if bad else f"{J.GREEN}✓{J.RESET}"
        print(f"{mark} {pid}  ({len(tests)} tests)")
        if bad or "-v" in sys.argv:
            print("\n".join(lines))
        problems_ok &= not bad
    print("\nall wrong solutions are caught" if problems_ok else "\nsome tests are too weak (see above)")
    sys.exit(0 if problems_ok else 1)


if __name__ == "__main__":
    main()
