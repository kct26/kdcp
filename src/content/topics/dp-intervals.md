---
title: DP: Intervals & Games
summary: dp[l][r] over subarrays, filled by increasing length.
---

When the answer for a segment `[l, r]` depends on smaller segments inside it, use `dp[l][r]`. Iterate by **length** so that all shorter segments are ready.

Two common shapes:

- **Take from the ends** (two-player games): `dp[l][r]` = best score difference for the player to move.
- **Split point** (merging slimes, matrix chain): `dp[l][r] = min over k of dp[l][k] + dp[k+1][r] + cost(l, r)`: O(n³).

```cpp
#include <bits/stdc++.h>
using namespace std;

// Removal Game: players take from either end; max score of first player
int main() {
    int n; cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long total = accumulate(a.begin(), a.end(), 0LL);
    // d[l][r] = (current player score) - (opponent score) on a[l..r]
    vector<vector<long long>> d(n, vector<long long>(n));
    for (int l = n - 1; l >= 0; l--)
        for (int r = l; r < n; r++)
            d[l][r] = (l == r) ? a[l]
                    : max(a[l] - d[l + 1][r], a[r] - d[l][r - 1]);
    cout << (total + d[0][n - 1]) / 2 << '\n';
}
```

## Problems
- [Removal Game](https://cses.fi/problemset/task/1097) Easy
- [Deque](https://atcoder.jp/contests/dp/tasks/dp_l) Easy
- [Slimes](https://atcoder.jp/contests/dp/tasks/dp_n) Medium
- [Rectangle Cutting](https://cses.fi/problemset/task/1744) Medium
- [Clear the String](https://codeforces.com/problemset/problem/1132/F) Hard
- [Zuma](https://codeforces.com/problemset/problem/607/B) Hard
