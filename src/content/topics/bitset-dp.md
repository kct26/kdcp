---
title: DP with Bitset
summary: Speed up boolean DP transitions 64× with bitwise operations.
---

When a DP table is **boolean** and the transition is a shift / OR / AND of a whole row, store each row as a `bitset`:

- Subset sum: `dp |= dp << w`.
- Reachability in a DAG: `reach[u] = {u} ∪ OR of reach[v]` over edges: process in reverse topological order.
- Transitive closure / counting triangles: `(adj[u] & adj[v]).count()`.

With n = 5·10⁴ the n²/64 ≈ 4·10⁷ word operations fit easily.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Reachable Nodes: for each node in a DAG, count nodes reachable from it
const int N = 50'001;
bitset<N> reach[N];

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0), order;
    for (int i = 0, a, b; i < m; i++) cin >> a >> b, adj[a].push_back(b), indeg[b]++;
    queue<int> q;
    for (int u = 1; u <= n; u++) if (!indeg[u]) q.push(u);
    while (!q.empty()) { int u = q.front(); q.pop(); order.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v); }
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i]; reach[u][u] = 1;
        for (int v : adj[u]) reach[u] |= reach[v];
    }
    for (int u = 1; u <= n; u++) cout << reach[u].count() << ' ';
}
```

## Problems
- [Money Sums](https://cses.fi/problemset/task/1745) Easy
- [Reachable Nodes](https://cses.fi/problemset/task/2138) Medium
- [Reachability Queries](https://cses.fi/problemset/task/2143) Hard
- [Alex and a TV Show](https://codeforces.com/problemset/problem/1097/F) Hard
