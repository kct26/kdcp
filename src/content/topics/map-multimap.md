---
title: map & multimap
summary: Sorted key → value storage, plus when to reach for unordered_map.
---

`map<K, V>` is a balanced BST keyed by `K`. `m[k]` inserts a default value if `k` is missing: use `m.count(k)` or `m.find(k)` to test without inserting.

`unordered_map` is a hash table with O(1) average operations, but it can be hacked with anti-hash tests on Codeforces. Use a custom hash (e.g. splitmix64) if you need it.

Common patterns: frequency counting, coordinate compression, prefix-sum counting.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Subarray Sums II: count subarrays with sum = x
int main() {
    int n; long long x; cin >> n >> x;
    map<long long, int> seen;             // prefix sum -> count
    seen[0] = 1;
    long long pre = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        long long a; cin >> a;
        pre += a;
        auto it = seen.find(pre - x);
        if (it != seen.end()) ans += it->second;
        seen[pre]++;
    }
    cout << ans << '\n';
}
```

## Problems
- [Registration System](https://codeforces.com/problemset/problem/4/C) Easy
- [Sum of Two Values](https://cses.fi/problemset/task/1640) Easy
- [Playlist](https://cses.fi/problemset/task/1141) Easy
- [Subarray Sums II](https://cses.fi/problemset/task/1661) Medium
- [Subarray Divisibility](https://cses.fi/problemset/task/1662) Medium
