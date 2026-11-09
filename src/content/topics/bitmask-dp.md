---
title: Bitmask DP
summary: DP over subsets when n ≤ 20.
---

The state includes a **mask** of which items are used. Common shapes:

- `dp[mask][last]`: Hamiltonian paths / TSP: O(2ⁿ · n²).
- `dp[mask]`: assign items one by one; the next index is `popcount(mask)` (Matching).
- **Submask enumeration**: `for (s = m; s; s = (s − 1) & m)` iterates all submasks; over all masks it is O(3ⁿ) total.
- `dp[mask] = (rides, last weight)`: pair-valued states (Elevator Rides).

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

// Matching: count perfect matchings in a bipartite graph, n ≤ 21
int main() {
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto& r : a) for (auto& x : r) cin >> x;
    vector<int> dp(1 << n, 0);
    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!dp[mask]) continue;
        int i = __builtin_popcount(mask);       // next man to match
        if (i == n) continue;
        for (int j = 0; j < n; j++)
            if (a[i][j] && !(mask >> j & 1))
                dp[mask | 1 << j] = (dp[mask | 1 << j] + dp[mask]) % MOD;
    }
    cout << dp[(1 << n) - 1] << '\n';
}
```

## Problems
- [Matching](https://atcoder.jp/contests/dp/tasks/dp_o) Easy
- [Hamiltonian Flights](https://cses.fi/problemset/task/1690) Medium
- [Kefa and Dishes](https://codeforces.com/problemset/problem/580/D) Medium
- [Elevator Rides](https://cses.fi/problemset/task/1653) Medium
- [Grouping](https://atcoder.jp/contests/dp/tasks/dp_u) Hard
