---
title: Calculus & Numerical Methods
summary: Integrate, find roots, and optimize when there's no closed form.
---

When a formula is hard to derive, approximate:

- **Simpson's rule**: `∫ f ≈ (h/3)(f₀ + 4f₁ + 2f₂ + 4f₃ + … + fₙ)` with an even number of intervals. Adaptive Simpson refines only where needed. Useful for areas and volumes of curved shapes.
- **Root finding**: bisection on a sign change (robust), or Newton's method `x ← x − f(x)/f'(x)` (fast near the root).
- **Optimization**: ternary search on unimodal functions; nest it for two variables when each slice is unimodal.
- **Derivatives in DP**: expected-value problems sometimes need `Σ x·pˣ`-type sums; differentiate a geometric series instead of looping.

Print enough digits (`setprecision(10)`) and compare doubles with an epsilon.

```cpp
#include <bits/stdc++.h>
using namespace std;

double simpson(function<double(double)> f, double a, double b, int n = 1000) {
    if (n % 2) n++;
    double h = (b - a) / n, s = f(a) + f(b);
    for (int i = 1; i < n; i++) s += f(a + i * h) * (i % 2 ? 4 : 2);
    return s * h / 3;
}

double bisect(function<double(double)> f, double lo, double hi) {   // f(lo) < 0 < f(hi)
    for (int it = 0; it < 100; it++) {
        double m = (lo + hi) / 2;
        (f(m) < 0 ? lo : hi) = m;
    }
    return lo;
}
```

## Problems
- [Weakness and Poorness](https://codeforces.com/problemset/problem/578/C) Medium
- [Little Pony and Expected Maximum](https://codeforces.com/problemset/problem/453/A) Easy
- [Restorer Distance](https://codeforces.com/problemset/problem/1355/E) Medium
