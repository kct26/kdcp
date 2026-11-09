---
title: bitset
summary: Pack 64 booleans per machine word for a ~64× constant-factor speedup.
---

`bitset<N>` stores `N` bits with a compile-time size. `&`, `|`, `^`, shifts and `count()` all run in O(N / 64).

The classic application is **subset sum**: bit `s` of `dp` is 1 if sum `s` is reachable. Adding an item of weight `w` is just `dp |= dp << w`.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Money Sums: print all reachable sums
int main() {
    int n; cin >> n;
    bitset<100001> dp;
    dp[0] = 1;
    for (int i = 0, w; i < n; i++) cin >> w, dp |= dp << w;
    cout << dp.count() - 1 << '\n';
    for (int s = 1; s <= 100000; s++) if (dp[s]) cout << s << ' ';
}
```

## Problems
- [Money Sums](https://cses.fi/problemset/task/1745) Easy
- [Reachable Nodes](https://cses.fi/problemset/task/2138) Medium
- [Alex and a TV Show](https://codeforces.com/problemset/problem/1097/F) Hard
