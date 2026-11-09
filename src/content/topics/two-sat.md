---
title: 2-SAT
summary: Satisfy a conjunction of 2-literal clauses with SCCs.
---

Each boolean variable `x` has two nodes: `x` and `¬x`. A clause `(a ∨ b)` becomes two implications: `¬a → b` and `¬b → a`.

The formula is satisfiable iff no variable has `x` and `¬x` in the same SCC. To build an assignment with Kosaraju (components numbered in topological order), set `x = true` iff `comp[x] > comp[¬x]`.

Typical models: "choose one of two options per item, with pairwise conflicts".

```cpp
#include <bits/stdc++.h>
using namespace std;

struct TwoSat {
    int n; vector<vector<int>> g, rg; vector<int> comp, order_; vector<bool> vis;
    TwoSat(int n) : n(n), g(2 * n), rg(2 * n) {}
    // literal: 2*i = x_i, 2*i+1 = not x_i
    void imply(int a, int b) { g[a].push_back(b); rg[b].push_back(a); }
    void either(int a, int b) { imply(a ^ 1, b); imply(b ^ 1, a); }   // a or b
    void dfs1(int u) { vis[u] = true; for (int v : g[u]) if (!vis[v]) dfs1(v); order_.push_back(u); }
    void dfs2(int u, int c) { comp[u] = c; for (int v : rg[u]) if (comp[v] < 0) dfs2(v, c); }
    bool solve(vector<bool>& val) {
        vis.assign(2 * n, false); comp.assign(2 * n, -1);
        for (int u = 0; u < 2 * n; u++) if (!vis[u]) dfs1(u);
        int c = 0;
        for (int i = 2 * n - 1; i >= 0; i--) if (comp[order_[i]] < 0) dfs2(order_[i], c++);
        val.assign(n, false);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            val[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return true;
    }
};
```

## Problems
- [Giant Pizza](https://cses.fi/problemset/task/1684) Medium
- [The Road to Berland is Paved With Good Intentions](https://codeforces.com/problemset/problem/228/E) Medium
- [Ring Road 2](https://codeforces.com/problemset/problem/27/D) Hard
