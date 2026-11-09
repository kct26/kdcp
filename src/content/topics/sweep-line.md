---
title: Sweep Line
summary: Turn geometry and interval problems into sorted events.
---

Convert objects into **events** sorted by coordinate (e.g. `+1` at an interval's start, `−1` after its end), then sweep while maintaining a data structure for the "active" set.

Typical problems:

- Max overlapping intervals / points covered by k segments.
- Union length or area of rectangles (sweep x, segment tree over y).
- Closest pair of points (sweep x, `set` ordered by y within the current strip).

Be careful with **tie-breaking** at equal coordinates: decide whether an end at x and a start at x overlap.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Covered Points Count: for each k, number of integer points covered by exactly k segments
int main() {
    int n; cin >> n;
    vector<pair<long long,int>> ev;
    for (int i = 0; i < n; i++) {
        long long l, r; cin >> l >> r;
        ev.push_back({l, +1}); ev.push_back({r + 1, -1});
    }
    sort(ev.begin(), ev.end());
    vector<long long> cnt(n + 1, 0);
    int cur = 0;
    for (size_t i = 0; i < ev.size(); i++) {
        if (i > 0) cnt[cur] += ev[i].first - ev[i - 1].first;
        cur += ev[i].second;
    }
    for (int k = 1; k <= n; k++) cout << cnt[k] << ' ';
}
```

## Problems
- [Restaurant Customers](https://cses.fi/problemset/task/1619) Easy
- [Covered Points Count](https://codeforces.com/problemset/problem/1000/C) Medium
- [Nested Ranges Count](https://cses.fi/problemset/task/2169) Medium
- [Minimum Euclidean Distance](https://cses.fi/problemset/task/2194) Hard
