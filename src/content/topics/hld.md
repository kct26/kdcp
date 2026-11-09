---
title: Heavy-Light Decomposition
summary: Split a tree into O(log n) chains per path for path queries with updates.
---

For each node, the child with the largest subtree is **heavy**; other edges are light. Any root-to-node path crosses at most O(log n) light edges, so it is covered by O(log n) heavy chains.

Lay out the DFS so each heavy chain is contiguous (visit the heavy child first). A path `u → v` becomes O(log n) ranges on a segment tree.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200'005;
vector<int> adj[N];
int par[N], dep[N], heavy[N], head[N], pos[N], sz[N], cur = 0;

int dfs(int u) {
    sz[u] = 1; heavy[u] = -1; int mx = 0;
    for (int v : adj[u]) if (v != par[u]) {
        par[v] = u; dep[v] = dep[u] + 1;
        int s = dfs(v); sz[u] += s;
        if (s > mx) mx = s, heavy[u] = v;
    }
    return sz[u];
}
void decompose(int u, int h) {
    head[u] = h; pos[u] = cur++;
    if (heavy[u] != -1) decompose(heavy[u], h);
    for (int v : adj[u]) if (v != par[u] && v != heavy[u]) decompose(v, v);
}
// query on path a-b: f(l, r) is a segment-tree query on [l, r]
template <class F> void path(int a, int b, F f) {
    for (; head[a] != head[b]; b = par[head[b]]) {
        if (dep[head[a]] > dep[head[b]]) swap(a, b);
        f(pos[head[b]], pos[b]);
    }
    if (dep[a] > dep[b]) swap(a, b);
    f(pos[a], pos[b]);
}
```

## Problems
- [Path Queries II](https://cses.fi/problemset/task/2134) Medium
- [Water Tree](https://codeforces.com/problemset/problem/343/D) Medium
- [Path Queries](https://cses.fi/problemset/task/1138) Easy
