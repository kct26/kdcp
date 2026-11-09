---
title: Binary Search
summary: Search a sorted array or binary search on the answer.
---

If a predicate `ok(x)` is monotonic (false … false, true … true), binary search finds the first true in O(log range) checks.

**Binary search on the answer**: instead of computing the optimum directly, ask "can we achieve at least x?" and search for the boundary. This often turns an optimization problem into an easier decision problem.

Write it with an invariant to avoid off-by-one bugs: `lo` is always false, `hi` is always true.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Factory Machines: min time to produce t products
int main() {
    int n; long long t; cin >> n >> t;
    vector<long long> k(n);
    for (auto& x : k) cin >> x;

    auto ok = [&](long long T) {
        long long made = 0;
        for (auto x : k) { made += T / x; if (made >= t) return true; }
        return false;
    };
    long long lo = 0, hi = 1e18;          // ok(lo) = false, ok(hi) = true
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        (ok(mid) ? hi : lo) = mid;
    }
    cout << hi << '\n';
}
```

## Problems
- [Factory Machines](https://cses.fi/problemset/task/1620) Easy
- [Hamburgers](https://codeforces.com/problemset/problem/371/C) Easy
- [Maximum Median](https://codeforces.com/problemset/problem/1201/C) Medium
- [Array Division](https://cses.fi/problemset/task/1085) Medium
- [Frodo and pillows](https://codeforces.com/problemset/problem/760/B) Medium
