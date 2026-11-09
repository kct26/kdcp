---
title: BFS
summary: Shortest paths in unweighted graphs, layer by layer.
---

Breadth-first search visits nodes in order of distance from the source, so the first time you reach a node is via a shortest path. Store `parent[v]` to reconstruct it.

Variants:

- **Multi-source BFS**: push all sources at distance 0 (Monsters).
- **Grid BFS**: neighbours are the 4 adjacent cells.
- **0-1 BFS**: edge weights 0 or 1: use a deque, push 0-edges to the front, 1-edges to the back.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Message Route: shortest path from 1 to n
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0, a, b; i < m; i++) cin >> a >> b, adj[a].push_back(b), adj[b].push_back(a);
    vector<int> dist(n + 1, -1), par(n + 1);
    queue<int> q; q.push(1); dist[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (dist[v] < 0) dist[v] = dist[u] + 1, par[v] = u, q.push(v);
    }
    if (dist[n] < 0) { cout << "IMPOSSIBLE\n"; return 0; }
    vector<int> path;
    for (int v = n; v != 1; v = par[v]) path.push_back(v);
    path.push_back(1); reverse(path.begin(), path.end());
    cout << path.size() << '\n';
    for (int v : path) cout << v << ' ';
}
```

## Problems
- [Message Route](https://cses.fi/problemset/task/1667) Easy
- [Labyrinth](https://cses.fi/problemset/task/1193) Easy
- [Monsters](https://cses.fi/problemset/task/1194) Medium
- [Single Source Shortest Path](https://open.kattis.com/problems/shortestpath1) Easy
