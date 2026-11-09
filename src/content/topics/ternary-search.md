---
title: Ternary Search
summary: Find the extremum of a unimodal function.
---

If `f` strictly decreases then strictly increases (unimodal), compare `f(m1)` and `f(m2)` at the two third-points and discard the third that cannot contain the minimum.

- On **reals**, run a fixed number of iterations (100 is plenty for doubles).
- On **integers**, shrink until the range is small, then brute force the rest. Alternatively, binary search on the sign of `f(x+1) − f(x)`.

Plateaus (equal values) break ternary search: make sure the function is strictly unimodal around the optimum.

```cpp
#include <bits/stdc++.h>
using namespace std;

// minimize a convex function f on [lo, hi] (reals)
double ternary(function<double(double)> f, double lo, double hi) {
    for (int it = 0; it < 100; it++) {
        double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2; else lo = m1;
    }
    return lo;
}

// integers
long long ternaryInt(function<long long(long long)> f, long long lo, long long hi) {
    while (hi - lo > 2) {
        long long m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2; else lo = m1;
    }
    long long best = lo;
    for (long long x = lo; x <= hi; x++) if (f(x) < f(best)) best = x;
    return best;
}
```

## Problems
- [Stick Lengths](https://cses.fi/problemset/task/1074) Easy
- [Weakness and Poorness](https://codeforces.com/problemset/problem/578/C) Medium
- [Restorer Distance](https://codeforces.com/problemset/problem/1355/E) Hard
