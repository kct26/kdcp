---
title: Max Flow & Bipartite Matching
summary: Dinic's algorithm, and matching as a special case of flow.
---

A flow network has capacities on edges; max flow pushes as much as possible from source `s` to sink `t`. Each edge has a **reverse residual edge** so flow can be undone.

**Dinic**: BFS builds a level graph, DFS sends blocking flow along increasing levels; repeat until `t` is unreachable.

**Bipartite matching**: source → left (cap 1), left → right (cap 1), right → sink (cap 1). Max flow = max matching. Disjoint paths, assignment and many scheduling problems reduce to this.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    struct E { int to; ll cap; };
    vector<E> e; vector<vector<int>> g; vector<int> lvl, it;
    Dinic(int n) : g(n), lvl(n), it(n) {}
    void add(int u, int v, ll c) { g[u].push_back(e.size()); e.push_back({v, c});
                                   g[v].push_back(e.size()); e.push_back({u, 0}); }
    bool bfs(int s, int t) {
        fill(lvl.begin(), lvl.end(), -1); lvl[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) { int u = q.front(); q.pop();
            for (int id : g[u]) if (e[id].cap && lvl[e[id].to] < 0) lvl[e[id].to] = lvl[u] + 1, q.push(e[id].to); }
        return lvl[t] >= 0;
    }
    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = it[u]; i < (int)g[u].size(); i++) {
            int id = g[u][i], v = e[id].to;
            if (e[id].cap && lvl[v] == lvl[u] + 1)
                if (ll d = dfs(v, t, min(f, e[id].cap))) { e[id].cap -= d; e[id ^ 1].cap += d; return d; }
        }
        return 0;
    }
    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) { fill(it.begin(), it.end(), 0); while (ll f = dfs(s, t, LLONG_MAX)) flow += f; }
        return flow;
    }
};
```

## Problems
- [Download Speed](https://cses.fi/problemset/task/1694) Easy
- [School Dance](https://cses.fi/problemset/task/1696) Medium
- [Distinct Routes](https://cses.fi/problemset/task/1711) Hard
- [Maximum Flow](https://open.kattis.com/problems/maxflow) Medium
- [Soldier and Traveling](https://codeforces.com/problemset/problem/546/E) Medium
