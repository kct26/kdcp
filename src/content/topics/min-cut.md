---
title: Minimum Cut
summary: Max flow = min cut; find the cut and model problems as cuts.
---

**Max-flow min-cut theorem**: the maximum flow equals the minimum total capacity of edges whose removal disconnects `s` from `t`.

To recover the cut: after max flow, mark every node reachable from `s` in the **residual graph**. Original edges from marked to unmarked nodes form a minimum cut.

Modeling with cuts: "each item goes to side A or B, with costs and penalties":

- `s → v` with capacity = cost of putting v in B,
- `v → t` with capacity = cost of putting v in A,
- `u → v` with capacity = penalty if u ∈ A and v ∈ B.

This solves project selection, image segmentation and many "choose a subset" problems.

```cpp
// after Dinic::maxflow(s, t) from the Max Flow topic:
vector<bool> side(n, false);
void mark(Dinic& d, int u, vector<bool>& side) {
    side[u] = true;
    for (int id : d.g[u])
        if (d.e[id].cap > 0 && !side[d.e[id].to]) mark(d, d.e[id].to, side);
}
// cut edges: original edges (u, v) with side[u] && !side[v]
```

## Problems
- [Police Chase](https://cses.fi/problemset/task/1695) Medium
- [Minimum Cut](https://open.kattis.com/problems/mincut) Medium
- [Download Speed](https://cses.fi/problemset/task/1694) Easy
