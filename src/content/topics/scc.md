---
title: Strongly Connected Components
summary: Collapse cycles in a directed graph to get a DAG of components.
---

In a directed graph, `u` and `v` are in the same SCC if each can reach the other. Contracting each SCC into one node yields a **DAG** (the condensation), on which you can run topological DP.

**Kosaraju**: (1) DFS on the graph, push nodes by exit time; (2) DFS on the **reversed** graph in decreasing exit time: each tree is one SCC. Components come out in topological order.

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> g, rg;
vector<int> order_, comp;
vector<bool> vis;

void dfs1(int u) { vis[u] = true; for (int v : g[u]) if (!vis[v]) dfs1(v); order_.push_back(u); }
void dfs2(int u, int c) { comp[u] = c; for (int v : rg[u]) if (comp[v] < 0) dfs2(v, c); }

int main() {
    cin >> n >> m;
    g.assign(n + 1, {}); rg.assign(n + 1, {});
    for (int i = 0, a, b; i < m; i++) cin >> a >> b, g[a].push_back(b), rg[b].push_back(a);
    vis.assign(n + 1, false); comp.assign(n + 1, -1);
    for (int u = 1; u <= n; u++) if (!vis[u]) dfs1(u);
    int k = 0;
    for (int i = n - 1; i >= 0; i--) if (comp[order_[i]] < 0) dfs2(order_[i], k++);
    cout << k << '\n';
    for (int u = 1; u <= n; u++) cout << comp[u] + 1 << ' ';
}
```

## Problems
- [Flight Routes Check](https://cses.fi/problemset/task/1682) Easy
- [Planets and Kingdoms](https://cses.fi/problemset/task/1683) Easy
- [Checkposts](https://codeforces.com/problemset/problem/427/C) Medium
- [Coin Collector](https://cses.fi/problemset/task/1686) Medium
