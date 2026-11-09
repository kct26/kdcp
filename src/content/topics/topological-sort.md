---
title: Topological Sort
summary: Order a DAG so every edge points forward, then run DP on it.
---

A topological order exists iff the directed graph has **no cycle**.

**Kahn's algorithm**: repeatedly remove a node with in-degree 0. If fewer than `n` nodes get removed, there is a cycle.

Once you have the order, many problems become a simple DP: longest path, number of paths, earliest finish time.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Course Schedule: print a valid order or IMPOSSIBLE
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0, a, b; i < m; i++) cin >> a >> b, adj[a].push_back(b), indeg[b]++;

    queue<int> q;
    for (int u = 1; u <= n; u++) if (!indeg[u]) q.push(u);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    if ((int)order.size() < n) { cout << "IMPOSSIBLE\n"; return 0; }
    for (int u : order) cout << u << ' ';
}
```

## Problems
- [Course Schedule](https://cses.fi/problemset/task/1679) Easy
- [Longest Path](https://atcoder.jp/contests/dp/tasks/dp_g) Easy
- [Game Routes](https://cses.fi/problemset/task/1681) Medium
- [Longest Flight Route](https://cses.fi/problemset/task/1680) Medium
- [Fox And Names](https://codeforces.com/problemset/problem/510/C) Medium
