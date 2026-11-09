---
title: Segment Tree
summary: Point updates and range queries for any associative operation.
---

A segment tree stores, for each node, the aggregate (sum, min, gcd, …) of a segment; children cover the two halves. Any range splits into O(log n) nodes.

The operation only needs to be **associative** with an identity element. Nodes can store structs, e.g. `(sum, best prefix, best suffix, best subarray)` for maximum subarray queries.

The iterative (bottom-up) version below is short and fast.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct SegTree {                       // range sum, point assign
    int n; vector<long long> t;
    SegTree(int n) : n(n), t(2 * n, 0) {}
    void update(int i, long long v) {
        for (t[i += n] = v; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1];
    }
    long long query(int l, int r) {    // [l, r)
        long long res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};
```

## Problems
- [Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) Easy
- [Dynamic Range Minimum Queries](https://cses.fi/problemset/task/1649) Easy
- [Xenia and Bit Operations](https://codeforces.com/problemset/problem/339/D) Easy
- [Hotel Queries](https://cses.fi/problemset/task/1143) Medium
- [Subarray Sum Queries](https://cses.fi/problemset/task/1190) Medium
- [Sereja and Brackets](https://codeforces.com/problemset/problem/380/C) Medium
