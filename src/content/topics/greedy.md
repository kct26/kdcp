---
title: Greedy
summary: Make the locally best choice and prove it with an exchange argument.
---

A greedy algorithm commits to the best-looking choice at each step. It is fast and short, but **often wrong**: always try to prove it or find a counterexample on small cases.

**Exchange argument**: take any optimal solution that differs from greedy. Show you can swap one element to match greedy without making it worse. Repeat → greedy is optimal.

Classic: to fit the most non-overlapping intervals, always take the one that **ends earliest**.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Movie Festival: max number of non-overlapping movies
int main() {
    int n; cin >> n;
    vector<pair<int,int>> m(n);           // (end, start)
    for (auto& [e, s] : m) cin >> s >> e;
    sort(m.begin(), m.end());
    int cnt = 0, last = 0;
    for (auto [e, s] : m) if (s >= last) cnt++, last = e;
    cout << cnt << '\n';
}
```

## Problems
- [Movie Festival](https://cses.fi/problemset/task/1629) Easy
- [Missing Coin Sum](https://cses.fi/problemset/task/2183) Medium
- [Woodcutters](https://codeforces.com/problemset/problem/545/C) Medium
- [Tasks and Deadlines](https://cses.fi/problemset/task/1630) Easy
- [Reading Books](https://cses.fi/problemset/task/1631) Medium
