---
title: Graphs & DFS
summary: Represent a graph with adjacency lists and explore it depth-first.
---

Store graphs as **adjacency lists**: `vector<int> adj[N]`. For weighted graphs use `vector<pair<int,int>>`.

Depth-first search goes as deep as possible before backtracking. Applications:

- Counting **connected components** (start a DFS from every unvisited node).
- **Cycle detection**: in a directed graph, an edge to a node still on the stack (gray) is a back edge.
- **Bipartite check**: 2-color while traversing.
- Subtree sizes and other values on trees.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200'005;
vector<int> adj[N];
bool vis[N];

void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u]) if (!vis[v]) dfs(v);
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        adj[a].push_back(b); adj[b].push_back(a);
    }
    int components = 0;
    for (int u = 1; u <= n; u++) if (!vis[u]) components++, dfs(u);
    cout << components << '\n';
}
```

## Problems
- [Counting Rooms](https://cses.fi/problemset/task/1192) Easy
- [Building Roads](https://cses.fi/problemset/task/1666) Easy
- [Building Teams](https://cses.fi/problemset/task/1668) Easy
- [Round Trip](https://cses.fi/problemset/task/1669) Medium
- [Subordinates](https://cses.fi/problemset/task/1674) Easy
- [Tree Diameter](https://cses.fi/problemset/task/1131) Medium
