---
title: Plane Geometry
summary: Cross products, orientation, polygons and convex hull, all in integers.
---

Almost everything starts with the **cross product** `cross(a, b) = aₓ·b_y − a_y·bₓ`:

- `cross(b − a, c − a) > 0` → c is to the **left** of a→b (counter-clockwise), `< 0` right, `= 0` collinear.
- **Polygon area** (shoelace): `½ |Σ cross(pᵢ, pᵢ₊₁)|`.
- **Segment intersection**: check orientations of each segment's endpoints relative to the other; handle collinear cases with bounding boxes.
- **Pick's theorem**: `A = I + B/2 − 1` for lattice polygons.

Use `long long` coordinates whenever possible; floating point only when unavoidable.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct P { ll x, y; P operator-(P o) const { return {x - o.x, y - o.y}; }
           bool operator<(P o) const { return tie(x, y) < tie(o.x, o.y); } };
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
ll cross(P o, P a, P b) { return cross(a - o, b - o); }

// Andrew's monotone chain, keeps collinear points on the hull
vector<P> hull(vector<P> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end(), [](P a, P b) { return a.x == b.x && a.y == b.y; }), p.end());
    if (p.size() < 3) return p;
    vector<P> h;
    for (int pass = 0; pass < 2; pass++) {
        size_t start = h.size();
        for (P q : p) {
            while (h.size() >= start + 2 && cross(h[h.size() - 2], h.back(), q) < 0) h.pop_back();
            h.push_back(q);
        }
        h.pop_back();
        reverse(p.begin(), p.end());
    }
    return h;
}
```

## Problems
- [Point Location Test](https://cses.fi/problemset/task/2189) Easy
- [Line Segment Intersection](https://cses.fi/problemset/task/2190) Medium
- [Polygon Area](https://cses.fi/problemset/task/2191) Easy
- [Point in Polygon](https://cses.fi/problemset/task/2192) Medium
- [Polygon Lattice Points](https://cses.fi/problemset/task/2193) Medium
- [Convex Hull](https://cses.fi/problemset/task/2195) Medium
- [Convex Hull](https://open.kattis.com/problems/convexhull) Medium
