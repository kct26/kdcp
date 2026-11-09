---
title: Sparse Table
summary: O(1) range minimum on a static array.
---

`sp[k][i]` = min of `a[i … i + 2ᵏ − 1]`. Build: `sp[k][i] = min(sp[k−1][i], sp[k−1][i + 2ᵏ⁻¹])`.

For a query `[l, r]`, let `k = ⌊log₂(r − l + 1)⌋`. The two blocks `[l, l + 2ᵏ)` and `(r − 2ᵏ, r]` cover the range and may overlap: fine for **idempotent** operations (min, max, gcd, AND, OR): giving O(1).

No updates allowed. For sums, use prefix sums instead.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Sparse {
    vector<vector<int>> sp;
    Sparse(const vector<int>& a) {
        int n = a.size(), K = __lg(n) + 1;
        sp.assign(K, a);
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                sp[k][i] = min(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);
    }
    int query(int l, int r) {          // inclusive
        int k = __lg(r - l + 1);
        return min(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};
```

## Problems
- [Static Range Minimum Queries](https://cses.fi/problemset/task/1647) Easy
- [Pair of Numbers](https://codeforces.com/problemset/problem/359/D) Medium
- [Company Queries I](https://cses.fi/problemset/task/1687) Medium
