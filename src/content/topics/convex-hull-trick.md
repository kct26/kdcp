---
title: Convex Hull Trick & Li Chao Tree
summary: dp[i] = min over j of (m_j · x_i + b_j) in O(log n).
---

If a transition looks like `dp[i] = min_j (dp[j] + b(j) · a(i))`, each `j` is a **line** `y = m·x + c` and you query the lowest line at `x = a(i)`.

- **Monotonic CHT**: slopes added in sorted order and queries sorted too: deque, O(1) amortized.
- **Li Chao tree**: arbitrary insertion order and queries: a segment tree over x where each node keeps the line that wins at its midpoint. O(log C) per operation, very hard to get wrong.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line { ll m, b; ll operator()(ll x) const { return m * x + b; } };

struct LiChao {                         // minimum over lines, x in [lo, hi)
    struct Node { Line ln; int l = -1, r = -1; };
    vector<Node> t; ll lo, hi;
    LiChao(ll lo, ll hi) : lo(lo), hi(hi) { t.push_back({{0, LLONG_MAX}}); }
    void add(Line nw, int x, ll l, ll r) {
        ll m = (l + r) / 2;
        bool lef = nw(l) < t[x].ln(l), mid = nw(m) < t[x].ln(m);
        if (mid) swap(t[x].ln, nw);
        if (r - l == 1) return;
        if (lef != mid) {               // new line wins on the left part
            if (t[x].l < 0) { t[x].l = t.size(); t.push_back({nw}); return; }
            add(nw, t[x].l, l, m);
        } else {
            if (t[x].r < 0) { t[x].r = t.size(); t.push_back({nw}); return; }
            add(nw, t[x].r, m, r);
        }
    }
    ll query(ll qx, int x, ll l, ll r) {
        if (x < 0) return LLONG_MAX;
        ll m = (l + r) / 2, res = t[x].ln(qx);
        if (r - l == 1) return res;
        return min(res, qx < m ? query(qx, t[x].l, l, m) : query(qx, t[x].r, m, r));
    }
    void add(Line ln) { add(ln, 0, lo, hi); }
    ll query(ll x) { return query(x, 0, lo, hi); }
};
```

## Problems
- [Frog 3](https://atcoder.jp/contests/dp/tasks/dp_z) Medium
- [Monster Game I](https://cses.fi/problemset/task/2084) Medium
- [Monster Game II](https://cses.fi/problemset/task/2085) Medium
- [Kalila and Dimna in the Logging Industry](https://codeforces.com/problemset/problem/319/C) Hard
- [Product Sum](https://codeforces.com/problemset/problem/631/E) Hard
