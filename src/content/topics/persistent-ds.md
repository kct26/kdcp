---
title: Persistent Data Structures
summary: Keep every past version by copying only the changed path.
---

A persistent segment tree never modifies a node: an update creates **new copies of the O(log n) nodes on the path** and reuses everything else. Each version is identified by its root.

Classic uses:

- **Range queries on old versions** (Range Queries and Copies).
- **k-th smallest in a subarray**: version `i` = counts of values in `a[1..i]`; query `root[r] − root[l−1]` and walk down.
- **Distinct elements in a range online**.

Allocate nodes from a big static pool: `n log n` nodes plus the initial tree.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXNODES = 200'005 * 40;
int L[MAXNODES], R[MAXNODES], cnt_ = 0;
long long sum_[MAXNODES];

int update(int prev, int l, int r, int pos, long long v) {   // returns new root
    int cur = ++cnt_;
    L[cur] = L[prev]; R[cur] = R[prev]; sum_[cur] = sum_[prev] + v;
    if (r - l > 1) {
        int m = (l + r) / 2;
        if (pos < m) L[cur] = update(L[prev], l, m, pos, v);
        else         R[cur] = update(R[prev], m, r, pos, v);
    }
    return cur;
}

// k-th smallest (0-indexed) among values inserted between versions u and v
int kth(int u, int v, int l, int r, int k) {
    if (r - l == 1) return l;
    int m = (l + r) / 2, left = sum_[L[v]] - sum_[L[u]];
    return k < left ? kth(L[u], L[v], l, m, k) : kth(R[u], R[v], m, r, k - left);
}
```

## Problems
- [Range Queries and Copies](https://cses.fi/problemset/task/1737) Medium
- [Army Creation](https://codeforces.com/problemset/problem/813/E) Hard
- [Distinct Values Queries](https://cses.fi/problemset/task/1734) Medium
