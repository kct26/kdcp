---
title: Change of Variables
summary: Swap what is a state and what is a value, or rotate coordinates.
---

Sometimes the "obvious" formulation is too big, but a re-parameterization is small.

**Swap state and value**: Knapsack with `W ≤ 10⁹` but values `≤ 10⁵`: instead of `dp[weight] = max value`, use `dp[value] = min weight`.

**Manhattan → Chebyshev**: with `u = x + y`, `v = x − y`:

`|x₁ − x₂| + |y₁ − y₂| = max(|u₁ − u₂|, |v₁ − v₂|)`

so "max Manhattan distance" becomes `max(maxU − minU, maxV − minV)`.

**Fix one variable**: iterate over the variable with the small range and solve the rest greedily or with a data structure.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Max Manhattan distance between any two points
int main() {
    int n; cin >> n;
    long long mxU = LLONG_MIN, mnU = LLONG_MAX, mxV = LLONG_MIN, mnV = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        long long x, y; cin >> x >> y;
        long long u = x + y, v = x - y;
        mxU = max(mxU, u); mnU = min(mnU, u);
        mxV = max(mxV, v); mnV = min(mnV, v);
    }
    cout << max(mxU - mnU, mxV - mnV) << '\n';
}
```

## Problems
- [Knapsack 2](https://atcoder.jp/contests/dp/tasks/dp_e) Easy
- [Dist Max](https://atcoder.jp/contests/abc178/tasks/abc178_e) Easy
- [Two Sets II](https://cses.fi/problemset/task/1093) Medium
- [Money Sums](https://cses.fi/problemset/task/1745) Easy
- [Elevator Rides](https://cses.fi/problemset/task/1653) Hard
