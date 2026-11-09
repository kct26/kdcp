---
title: Merge Small to Large
summary: Always merge the smaller set into the larger one for O(n log n) total.
---

When merging sets repeatedly, insert elements of the **smaller** set into the **larger** one. Each element moves only when its set at least doubles in size, so it moves at most O(log n) times.

On trees: compute a set (or map) for every subtree by merging children's sets into the largest child's. Use `swap` to adopt the child's container in O(1).

```cpp
#include <bits/stdc++.h>
using namespace std;

// Distinct Colors: number of distinct colors in each subtree
const int N = 200'005;
vector<int> adj[N];
int color[N], ans[N];
set<int> s[N];

void dfs(int u, int p) {
    s[u].insert(color[u]);
    for (int v : adj[u]) if (v != p) {
        dfs(v, u);
        if (s[v].size() > s[u].size()) swap(s[u], s[v]);
        for (int c : s[v]) s[u].insert(c);
        s[v].clear();
    }
    ans[u] = s[u].size();
}
```

## Problems
- [Distinct Colors](https://cses.fi/problemset/task/1139) Medium
- [Lomsat gelral](https://codeforces.com/problemset/problem/600/E) Medium
- [Tree Requests](https://codeforces.com/problemset/problem/570/D) Hard
