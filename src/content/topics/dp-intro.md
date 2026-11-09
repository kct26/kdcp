---
title: Introduction to DP
summary: States, transitions, base cases and the classic problems.
---

Dynamic programming = recursion + memoization. Define:

1. **State**: what `dp[...]` means, in one sentence.
2. **Transition**: how a state is built from smaller ones.
3. **Base case** and **answer**.

Classics to know by heart: coin change, 0/1 knapsack, longest common subsequence, edit distance, grid paths.

```cpp
#include <bits/stdc++.h>
using namespace std;

// 0/1 Knapsack (Book Shop): max pages with total price ≤ x
int main() {
    int n, x; cin >> n >> x;
    vector<int> h(n), s(n);
    for (auto& v : h) cin >> v;
    for (auto& v : s) cin >> v;
    vector<int> dp(x + 1, 0);              // dp[c] = best pages with cost ≤ c
    for (int i = 0; i < n; i++)
        for (int c = x; c >= h[i]; c--)    // iterate down: each book once
            dp[c] = max(dp[c], dp[c - h[i]] + s[i]);
    cout << dp[x] << '\n';
}
```

## Problems
- [Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a) Easy
- [Dice Combinations](https://cses.fi/problemset/task/1633) Easy
- [Minimizing Coins](https://cses.fi/problemset/task/1634) Easy
- [Book Shop](https://cses.fi/problemset/task/1158) Easy
- [LCS](https://atcoder.jp/contests/dp/tasks/dp_f) Medium
- [Edit Distance](https://cses.fi/problemset/task/1639) Medium
- [Knapsack](https://open.kattis.com/problems/knapsack) Medium
