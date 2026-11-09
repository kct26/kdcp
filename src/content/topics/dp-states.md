---
title: DP: Designing States
summary: Add exactly the information you need to the state, nothing more.
---

When a straightforward DP fails, the state is usually missing something. Ask: *what do I need to know about the past to make the next decision?*

- **Last choice**: Vacation: `dp[i][last activity]`.
- **Counting vs. order**: Coin Combinations I counts ordered ways (loop sums outside), II counts unordered ways (loop coins outside).
- **LIS in O(n log n)**: `d[len]` = smallest possible tail of an increasing subsequence of length `len`; update with `lower_bound`.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Longest strictly increasing subsequence in O(n log n)
int lis(const vector<int>& a) {
    vector<int> d;                         // d[k] = min tail of length k+1
    for (int x : a) {
        auto it = lower_bound(d.begin(), d.end(), x);
        if (it == d.end()) d.push_back(x); else *it = x;
    }
    return d.size();
}
```

## Problems
- [Vacation](https://atcoder.jp/contests/dp/tasks/dp_c) Easy
- [Coin Combinations II](https://cses.fi/problemset/task/1636) Easy
- [Boredom](https://codeforces.com/problemset/problem/455/A) Easy
- [Increasing Subsequence](https://cses.fi/problemset/task/1145) Medium
- [Array Description](https://cses.fi/problemset/task/1746) Medium
- [Counting Towers](https://cses.fi/problemset/task/2413) Hard
