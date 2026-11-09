---
title: set & multiset
summary: A balanced BST with sorted order and O(log n) insert, erase and search.
---

`set` stores unique sorted keys; `multiset` allows duplicates. Both are red-black trees.

- `lower_bound(x)`: first element `≥ x`
- `upper_bound(x)`: first element `> x`
- `prev(it)` / `next(it)`: neighbours

In a multiset, `ms.erase(x)` removes **all** copies of `x`. To remove one copy use `ms.erase(ms.find(x))`.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Concert Tickets: each customer takes the most expensive ticket ≤ their max
int main() {
    int n, m; cin >> n >> m;
    multiset<int> tickets;
    for (int i = 0, h; i < n; i++) cin >> h, tickets.insert(h);
    while (m--) {
        int t; cin >> t;
        auto it = tickets.upper_bound(t);
        if (it == tickets.begin()) { cout << -1 << '\n'; continue; }
        --it;
        cout << *it << '\n';
        tickets.erase(it);                // erase one copy
    }
}
```

## Problems
- [Concert Tickets](https://cses.fi/problemset/task/1091) Easy
- [Traffic Lights](https://cses.fi/problemset/task/1163) Medium
- [Towers](https://cses.fi/problemset/task/1073) Medium
- [Sliding Window Median](https://cses.fi/problemset/task/1076) Medium
- [Coffee Break](https://codeforces.com/problemset/problem/1041/C) Medium
