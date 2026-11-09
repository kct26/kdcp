---
title: Segment Tree Techniques
summary: Lazy propagation, walking down the tree, and merging rich node info.
---

**Lazy propagation**: for range updates, store a pending tag on a node and push it to the children only when you descend. You must define how a tag changes the node's value and how two tags compose.

**Descending the tree**: find the first index with prefix sum ≥ k, or the first position with value ≥ x, in O(log n) by choosing the left or right child at each step (not binary search + query, which is O(log² n)).

**Offline tricks**: sort queries by right endpoint and sweep (Distinct Values Queries).

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// range add, range sum
struct Lazy {
    int n; vector<ll> t, lz;
    Lazy(int n) : n(n), t(4 * n), lz(4 * n) {}
    void apply(int x, int len, ll v) { t[x] += v * len; lz[x] += v; }
    void push(int x, int l, int r) {
        if (!lz[x]) return;
        int m = (l + r) / 2;
        apply(2 * x, m - l, lz[x]); apply(2 * x + 1, r - m, lz[x]); lz[x] = 0;
    }
    void add(int a, int b, ll v, int x, int l, int r) {   // [a, b), node covers [l, r)
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) { apply(x, r - l, v); return; }
        push(x, l, r);
        int m = (l + r) / 2;
        add(a, b, v, 2 * x, l, m); add(a, b, v, 2 * x + 1, m, r);
        t[x] = t[2 * x] + t[2 * x + 1];
    }
    ll sum(int a, int b, int x, int l, int r) {
        if (b <= l || r <= a) return 0;
        if (a <= l && r <= b) return t[x];
        push(x, l, r);
        int m = (l + r) / 2;
        return sum(a, b, 2 * x, l, m) + sum(a, b, 2 * x + 1, m, r);
    }
    void add(int a, int b, ll v) { add(a, b, v, 1, 0, n); }
    ll sum(int a, int b) { return sum(a, b, 1, 0, n); }
};
```

## Problems
- [Range Update Queries](https://cses.fi/problemset/task/1651) Easy
- [Range Updates and Sums](https://cses.fi/problemset/task/1735) Medium
- [Circular RMQ](https://codeforces.com/problemset/problem/52/C) Medium
- [Polynomial Queries](https://cses.fi/problemset/task/1736) Hard
- [XOR on Segment](https://codeforces.com/problemset/problem/242/E) Hard
- [Distinct Values Queries](https://cses.fi/problemset/task/1734) Medium
