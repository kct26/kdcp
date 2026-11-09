---
title: Bridges & Articulation Points
summary: Find edges and vertices whose removal disconnects the graph.
---

Run DFS and record `tin[u]` (entry time) and `low[u]`: the smallest `tin` reachable from `u`'s subtree using **at most one back edge**.

- Tree edge `(u, v)` is a **bridge** iff `low[v] > tin[u]`.
- Non-root `u` is an **articulation point** iff some child `v` has `low[v] ≥ tin[u]`. The root is one iff it has ≥ 2 DFS children.

Skip the edge you came from by **edge id**, not by parent vertex, so multi-edges are handled correctly.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100'005;
vector<pair<int,int>> adj[N];          // (to, edge id)
int tin[N], low[N], timer_ = 0;
vector<int> bridges;                   // edge ids

void dfs(int u, int pe) {
    tin[u] = low[u] = ++timer_;
    for (auto [v, id] : adj[u]) {
        if (id == pe) continue;
        if (tin[v]) low[u] = min(low[u], tin[v]);
        else {
            dfs(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) bridges.push_back(id);
        }
    }
}
```

## Problems
- [Necessary Roads](https://cses.fi/problemset/task/2076) Medium
- [Necessary Cities](https://cses.fi/problemset/task/2077) Medium
- [Bertown roads](https://codeforces.com/problemset/problem/118/E) Medium
- [Flight Routes Check](https://cses.fi/problemset/task/1682) Medium
