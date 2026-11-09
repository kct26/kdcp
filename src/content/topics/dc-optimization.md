---
title: Divide & Conquer Optimization
summary: dp[k][i] = min_j dp[k−1][j] + cost(j, i) with monotone optimal j.
---

For layered DP `dp[k][i] = min_{j < i} (dp[k−1][j] + C(j, i))`, let `opt[i]` be the best `j`. If `opt[i] ≤ opt[i+1]` (true when C satisfies the **quadrangle inequality**), compute one layer recursively:

- solve the middle `mid` by scanning `j ∈ [optL, optR]`;
- recurse left with `[optL, opt[mid]]` and right with `[opt[mid], optR]`.

Each recursion level scans O(n) candidates → O(n log n) per layer. If `C(j, i)` isn't O(1), maintain it with moving pointers (like Mo's).

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, K;
vector<ll> prv, cur;
ll C(int j, int i);                    // cost of grouping (j, i], problem-specific

void solve(int l, int r, int optL, int optR) {
    if (l > r) return;
    int mid = (l + r) / 2, best = optL;
    cur[mid] = LLONG_MAX;
    for (int j = optL; j <= min(mid - 1, optR); j++) {
        ll v = prv[j] + C(j, mid);
        if (v < cur[mid]) cur[mid] = v, best = j;
    }
    solve(l, mid - 1, optL, best);
    solve(mid + 1, r, best, optR);
}
// for each layer k: solve(1, n, 0, n - 1); prv = cur;
```

## Problems
- [Ciel and Gondolas](https://codeforces.com/problemset/problem/321/E) Hard
- [Yet Another Minimization Problem](https://codeforces.com/problemset/problem/868/F) Hard
- [Array Division](https://cses.fi/problemset/task/1085) Easy
