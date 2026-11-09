---
title: Lowest Common Ancestor
summary: Binary lifting for LCA, k-th ancestor and path queries.
---

**Binary lifting**: `up[k][v]` = the 2ᵏ-th ancestor of `v`. To jump `d` levels, decompose `d` into powers of two.

LCA(u, v): lift the deeper node to the same depth; if equal, done. Otherwise lift both from the highest power down while their ancestors differ; the answer is the parent.

- Distance: `depth[u] + depth[v] − 2·depth[lca]`.
- Path counts: add +1 at u and v, −1 at lca and parent(lca), then sum subtrees.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200'005, LOG = 18;
vector<int> adj[N];
int up[LOG][N], depth_[N];

void dfs(int u, int p) {
    up[0][u] = p;
    for (int k = 1; k < LOG; k++) up[k][u] = up[k - 1][up[k - 1][u]];
    for (int v : adj[u]) if (v != p) depth_[v] = depth_[u] + 1, dfs(v, u);
}
int lift(int v, int d) { for (int k = 0; k < LOG; k++) if (d >> k & 1) v = up[k][v]; return v; }
int lca(int a, int b) {
    if (depth_[a] < depth_[b]) swap(a, b);
    a = lift(a, depth_[a] - depth_[b]);
    if (a == b) return a;
    for (int k = LOG - 1; k >= 0; k--) if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
    return up[0][a];
}
// call dfs(root, root) so the root's ancestor is itself
```

## Problems
- [Company Queries I](https://cses.fi/problemset/task/1687) Easy
- [Company Queries II](https://cses.fi/problemset/task/1688) Easy
- [Distance Queries](https://cses.fi/problemset/task/1135) Easy
- [Counting Paths](https://cses.fi/problemset/task/1136) Medium
- [Fools and Roads](https://codeforces.com/problemset/problem/191/C) Medium
