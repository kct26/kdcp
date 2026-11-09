---
title: DSU & DSU Rollback
summary: Merge sets and test connectivity in near-constant time and undo merges.
---

A disjoint set union keeps a forest; each set is a tree identified by its root.

- **Path compression** + **union by size** → almost O(1) per operation.
- Kruskal's MST: sort edges by weight, add an edge if its endpoints are in different sets.

**Rollback**: drop path compression, keep union by size (depth stays O(log n)), and push every change on a stack so you can undo the last union. This powers offline dynamic connectivity (segment tree over time).

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    vector<pair<int,int>> hist;            // for rollback: (child root, parent root)
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { while (x != p[x]) x = p[x]; return x; }   // no compression
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b]; hist.push_back({b, a});
        return true;
    }
    void rollback() {
        auto [b, a] = hist.back(); hist.pop_back();
        p[b] = b; sz[a] -= sz[b];
    }
};
```

## Problems
- [Road Construction](https://cses.fi/problemset/task/1676) Easy
- [Road Reparation](https://cses.fi/problemset/task/1675) Easy
- [Union-Find](https://open.kattis.com/problems/unionfind) Easy
- [Roads not only in Berland](https://codeforces.com/problemset/problem/25/D) Medium
- [Bipartite Checking](https://codeforces.com/problemset/problem/813/F) Hard
