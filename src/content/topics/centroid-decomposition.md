---
title: Centroid Decomposition
summary: Recursively split a tree at its centroid to handle all paths.
---

The **centroid** is a node whose removal leaves components of size ≤ n/2. Remove it, recurse on each component. The recursion depth is O(log n).

Every path in the tree passes through exactly one centroid that is the "highest" in the decomposition, so "count/aggregate over all paths" becomes "for each centroid, combine paths going through it".

The centroid tree also answers "nearest marked node" queries: walk up O(log n) centroid ancestors.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200'005;
vector<int> adj[N];
int sz[N]; bool removed_[N];
int cpar[N];                           // parent in the centroid tree

int calcSize(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) if (v != p && !removed_[v]) sz[u] += calcSize(v, u);
    return sz[u];
}
int findCentroid(int u, int p, int total) {
    for (int v : adj[u]) if (v != p && !removed_[v] && sz[v] * 2 > total)
        return findCentroid(v, u, total);
    return u;
}
void build(int u, int p) {
    int c = findCentroid(u, -1, calcSize(u, -1));
    cpar[c] = p; removed_[c] = true;
    // ... process all paths through c here ...
    for (int v : adj[c]) if (!removed_[v]) build(v, c);
}
```

## Problems
- [Finding a Centroid](https://cses.fi/problemset/task/2079) Easy
- [Fixed-Length Paths I](https://cses.fi/problemset/task/2080) Medium
- [Fixed-Length Paths II](https://cses.fi/problemset/task/2081) Hard
- [Ciel the Commander](https://codeforces.com/problemset/problem/321/C) Medium
- [Xenia and Tree](https://codeforces.com/problemset/problem/342/E) Hard
