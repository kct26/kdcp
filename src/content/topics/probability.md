---
title: Probability
summary: DP over probabilities, and when to count instead.
---

Two ways to compute a probability:

1. **Count**: favourable outcomes / total outcomes (all equally likely).
2. **DP**: `dp[state]` = probability of reaching it; transitions multiply by the probability of each move.

Use `double` (print with enough digits, e.g. `setprecision(6)`), or work mod p with modular inverses when the problem asks for `P · Q⁻¹`.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Coins: n coins, coin i shows heads with prob p[i];
// probability of more heads than tails
int main() {
    int n; cin >> n;
    vector<double> p(n);
    for (auto& x : p) cin >> x;
    vector<double> dp(n + 1, 0);           // dp[h] = P(h heads so far)
    dp[0] = 1;
    for (int i = 0; i < n; i++)
        for (int h = i + 1; h >= 0; h--)
            dp[h] = dp[h] * (1 - p[i]) + (h ? dp[h - 1] * p[i] : 0);
    double ans = 0;
    for (int h = n / 2 + 1; h <= n; h++) ans += dp[h];
    cout << setprecision(10) << ans << '\n';
}
```

## Problems
- [Coins](https://atcoder.jp/contests/dp/tasks/dp_i) Easy
- [Dice Probability](https://cses.fi/problemset/task/1725) Easy
- [Inversion Probability](https://cses.fi/problemset/task/1728) Medium
- [Bag of mice](https://codeforces.com/problemset/problem/148/D) Medium
- [Ilya and Escalator](https://codeforces.com/problemset/problem/518/D) Medium
