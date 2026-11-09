---
title: Euler Tour on Trees
summary: Flatten a tree so every subtree is a contiguous range.
---

Record `tin[u]` when DFS enters u and `tout[u]` when it leaves. The subtree of u is exactly the positions `[tin[u], tout[u]]`, so subtree queries become **range queries** on an array (BIT / segment tree).

Path-to-root sums: add `+x` at `tin[u]` and `−x` at `tout[u] + 1`; the prefix sum at `tin[v]` gives the sum on the root→v path.

The other "Euler tour" stores every edge traversal (length 2n − 1); LCA = minimum depth between the two occurrences (RMQ with a sparse table).

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200'005;
vector<int> adj[N];
int tin[N], tout[N], timer_ = 0;

void dfs(int u, int p) {
    tin[u] = timer_++;
    for (int v : adj[u]) if (v != p) dfs(v, u);
    tout[u] = timer_ - 1;              // subtree of u = [tin[u], tout[u]]
}
// Subtree Queries: put value of u at index tin[u] in a BIT,
// update a node = point update, subtree sum = range sum(tin[u], tout[u])
```

## Problems
- [Subtree Queries](https://cses.fi/problemset/task/1137) Easy
- [Path Queries](https://cses.fi/problemset/task/1138) Medium
- [New Year Tree](https://codeforces.com/problemset/problem/620/E) Medium
- [Water Tree](https://codeforces.com/problemset/problem/343/D) Hard
