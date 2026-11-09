---
title: DP: Speeding Up Transitions
summary: Prefix sums, monotonic queues and segment trees inside the DP loop.
---

If the state space is fine but each transition loops over a range, speed up the range query:

- **Prefix sums**: `dp[i] = Σ dp[j]` for `j` in a window → O(1) per state (Candies).
- **Monotonic deque**: `dp[i] = min dp[j]` over a sliding window.
- **Segment tree / BIT**: `dp[i] = max dp[j] + w` over `h[j] < h[i]` (Flowers).
- **Sort events**: process projects by end time and binary search the last compatible one.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Projects: weighted interval scheduling in O(n log n)
int main() {
    int n; cin >> n;
    vector<array<long long,3>> p(n);       // end, start, reward
    for (auto& [b, a, r] : p) cin >> a >> b >> r;
    sort(p.begin(), p.end());
    vector<long long> ends(n), dp(n + 1, 0);
    for (int i = 0; i < n; i++) ends[i] = p[i][0];
    for (int i = 0; i < n; i++) {
        // number of projects ending strictly before start
        int j = lower_bound(ends.begin(), ends.end(), p[i][1]) - ends.begin();
        dp[i + 1] = max(dp[i], dp[j] + p[i][2]);
    }
    cout << dp[n] << '\n';
}
```

## Problems
- [Candies](https://atcoder.jp/contests/dp/tasks/dp_m) Medium
- [Projects](https://cses.fi/problemset/task/1140) Medium
- [Flowers](https://atcoder.jp/contests/dp/tasks/dp_q) Medium
- [Increasing Subsequence II](https://cses.fi/problemset/task/1748) Hard
- [Intervals](https://atcoder.jp/contests/dp/tasks/dp_w) Hard
