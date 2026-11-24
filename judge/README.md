# KDCP judge

There are two ways to judge the extra practice problems.

## On the website

Each problem page has a **Submit** box: paste C++ code and press Submit. The page runs the code on [Compiler Explorer](https://godbolt.org) (GCC 14, `-O2 -std=c++17`, 3 s per test) against 9 tests: the samples, 6 small random tests and 2 at full size. Small tests show the first wrong token; on large tests the program's output is checksummed inside the run (see `web/wrapper_tail.cpp`), because the runner returns at most 32 KB of output.

The tests are generated from `gen.cpp` and `sol.cpp` by `python3 judge/web/build_tests.py`, which writes `public/judge/` (not committed). The deploy workflow runs it before every build; run it yourself before `npm run dev` to try the judge locally.

## On your computer

`judge.py` compiles your C++ solution, runs it on the sample plus random tests (small ones and ones at the maximum size), and compares your output with the reference solution token by token.

Needs `python3` and a C++17 compiler (`g++` or `clang++`; set `CXX=clang++` to choose).

```bash
python3 judge/judge.py --list                       # all problems
python3 judge/judge.py s2-collisions my.cpp         # judge a solution
python3 judge/judge.py s2-collisions my.cpp -n 50   # more random tests
python3 judge/judge.py s2-collisions my.cpp -t 5    # time limit 5 s (default 3)
```

On a wrong answer it prints the first differing token and saves the failing input to `judge/.build/failed-<problem>.txt`, so you can rerun it with `./a.out < judge/.build/failed-<problem>.txt`.

## Problem folder

Each problem lives in `judge/problems/<id>/`:

| File | Purpose |
| --- | --- |
| `statement.md` | Statement shown on the website. The ` ```input ` / ` ```output ` blocks are the samples. |
| `sol.cpp` | Reference solution; it defines the expected output. |
| `gen.cpp` | Test generator: `./gen <seed> <small|large>` prints one input file. |
| `brute.cpp` | Slow but simple solution, used to double-check `sol.cpp` (and must be too slow for the large tests). |
| `solution.cpp` | The solution shown on the website's Solution tab, written in the class template. |

Before publishing a new problem, check the reference against the brute force:

```bash
python3 judge/judge.py <id> --stress -n 300
```

## Are the tests strong enough?

`judge/mutants/<id>/` holds wrong solutions for each problem: `bad-*.cpp` files and small edits to `sol.cpp` listed in `mutants.json` (typical mistakes: off-by-one, `int` overflow, a wrong greedy, a missing edge case). `ok-*.cpp` files are other correct solutions. This check runs all of them against the exact website tests:

```bash
python3 judge/web/build_tests.py && python3 judge/check_tests.py
```

Every wrong solution (and the slow `brute.cpp`) must fail at least one test, and `sol.cpp`, `solution.cpp` and every `ok-*.cpp` must pass them all. When someone finds a wrong solution that gets Accepted, add it as `bad-*.cpp`, then make `gen.cpp` produce inputs that catch it.

Generators use only `mt19937_64` with plain modulo and their own shuffle, so the tests are identical on every platform (the site's tests are built on Linux in CI).

The front matter of `statement.md` sets the title, the session, the order inside the session, and the lesson (a slug from `src/content/roadmap.ts`) where it appears under "Extra practice".
