# KDCP local judge

A judge for the extra practice problems, which have no online judge. It compiles your C++ solution, runs it on the sample plus random tests (small ones and ones at the maximum size), and compares your output with the reference solution token by token.

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
| `brute.cpp` | Slow but simple solution, used to double-check `sol.cpp`. |

Before publishing a new problem, check the reference against the brute force:

```bash
python3 judge/judge.py <id> --stress -n 300
```

The front matter of `statement.md` sets the title, the session, the order inside the session, and the lesson (a slug from `src/content/roadmap.ts`) where it appears under "Extra practice".
