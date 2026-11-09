---
title: Dijkstra with a Heap
summary: Single-source shortest paths with non-negative weights.
---

Keep a min-heap of `(distance, node)`. Pop the closest node; if the popped distance is stale, skip it; otherwise relax its edges.

**Negative edges break Dijkstra**: use Bellman-Ford (O(VE)) instead. For all pairs on small graphs, use Floyd-Warshall (O(V³)).

Useful trick: run Dijkstra on an **expanded state** `(node, extra info)`: e.g. "have I used the discount coupon yet?".

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) { int a, b; ll c; cin >> a >> b >> c; adj[a].push_back({b, c}); }
    vector<ll> dist(n + 1, LLONG_MAX);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    dist[1] = 0; pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;           // stale entry
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) dist[v] = d + w, pq.push({dist[v], v});
    }
    for (int u = 1; u <= n; u++) cout << dist[u] << ' ';
}
```

## Problems
- [Shortest Routes I](https://cses.fi/problemset/task/1671) Easy
- [Shortest Routes II](https://cses.fi/problemset/task/1672) Easy
- [Flight Discount](https://cses.fi/problemset/task/1195) Medium
- [Investigation](https://cses.fi/problemset/task/1202) Medium
- [Flight Routes](https://cses.fi/problemset/task/1196) Hard
- [Dijkstra?](https://codeforces.com/problemset/problem/20/C) Easy
