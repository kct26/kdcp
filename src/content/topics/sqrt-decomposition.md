---
title: Square Root Decomposition
summary: Blocks of size √n, and Mo's algorithm for offline range queries.
---

**Blocks**: split the array into blocks of size `B ≈ √n` and keep an aggregate per block. A query touches O(√n) whole blocks and O(√n) loose elements.

**Mo's algorithm**: answer offline range queries when you can add/remove one element at a time. Sort queries by `(l / B, r)` and move two pointers; total pointer movement is O((n + q) √n).

**Heavy/light split by threshold**: handle "big" items (> √n of them is impossible) separately from small ones.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Mo's algorithm: number of distinct values in [l, r]
int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    { auto v = a; sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
      for (auto& x : a) x = lower_bound(v.begin(), v.end(), x) - v.begin(); }

    vector<array<int,3>> qs(q);
    for (int i = 0; i < q; i++) { cin >> qs[i][0] >> qs[i][1]; qs[i][0]--; qs[i][1]--; qs[i][2] = i; }
    const int B = max(1, (int)sqrt(n));
    sort(qs.begin(), qs.end(), [&](auto& x, auto& y) {
        if (x[0] / B != y[0] / B) return x[0] < y[0];
        return (x[0] / B & 1) ? x[1] > y[1] : x[1] < y[1];
    });

    vector<int> cnt(n, 0), ans(q);
    int distinct = 0, L = 0, R = -1;
    auto add = [&](int i) { if (cnt[a[i]]++ == 0) distinct++; };
    auto rem = [&](int i) { if (--cnt[a[i]] == 0) distinct--; };
    for (auto [l, r, id] : qs) {
        while (R < r) add(++R);
        while (L > l) add(--L);
        while (R > r) rem(R--);
        while (L < l) rem(L++);
        ans[id] = distinct;
    }
    for (int x : ans) cout << x << '\n';
}
```

## Problems
- [Distinct Values Queries](https://cses.fi/problemset/task/1734) Medium
- [Powerful array](https://codeforces.com/problemset/problem/86/D) Medium
- [Holes](https://codeforces.com/problemset/problem/13/E) Hard
