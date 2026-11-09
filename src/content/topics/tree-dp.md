---
title: DP on Trees
summary: Combine children's answers bottom-up; reroot to get every root.
---

Root the tree, run DFS, and compute `dp[u]` from `dp[children]`. Examples: max independent set (`dp[u][taken?]`), tree matching, subtree sizes.

**Rerooting**: to get the answer *for every possible root*, do two passes:

1. Down pass: `down[u]` = answer for u's subtree.
2. Up pass: `up[v]` = answer for the part of the tree **outside** v's subtree, computed from `up[u]` and v's siblings (use prefix/suffix aggregates if the combine is not invertible).

```cpp
#include <bits/stdc++.h>
using namespace std;

// Tree Distances II: for each node, sum of distances to all others (rerooting)
const int N = 200'005;
int n; vector<int> adj[N];
long long sz[N], down_[N], ans[N];

void dfs1(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) if (v != p) dfs1(v, u), sz[u] += sz[v], down_[u] += down_[v] + sz[v];
}
void dfs2(int u, int p) {
    for (int v : adj[u]) if (v != p) {
        // moving root u -> v: sz[v] nodes get closer, n - sz[v] get farther
        ans[v] = ans[u] - sz[v] + (n - sz[v]);
        dfs2(v, u);
    }
}
int main() {
    cin >> n;
    for (int i = 0, a, b; i < n - 1; i++) cin >> a >> b, adj[a].push_back(b), adj[b].push_back(a);
    dfs1(1, 0); ans[1] = down_[1]; dfs2(1, 0);
    for (int u = 1; u <= n; u++) cout << ans[u] << ' ';
}
```

## Problems
- [Independent Set](https://atcoder.jp/contests/dp/tasks/dp_p) Easy
- [Tree Matching](https://cses.fi/problemset/task/1130) Easy
- [Tree Distances I](https://cses.fi/problemset/task/1132) Medium
- [Tree Distances II](https://cses.fi/problemset/task/1133) Medium
- [Tree with Maximum Cost](https://codeforces.com/problemset/problem/1092/F) Medium
- [Subtree](https://atcoder.jp/contests/dp/tasks/dp_v) Hard
