---
title: Two Pointers
summary: Move two indices monotonically to turn O(n²) scans into O(n).
---

When a window `[l, r]` that is valid stays valid after shrinking (or the condition is monotonic), advance `r` and move `l` forward only as needed. Each pointer moves at most n times → O(n).

Two flavours:

- **Sliding window**: both pointers move right (longest subarray with sum ≤ k).
- **Opposite ends**: on a sorted array, `l` from the left, `r` from the right (pair with given sum).

```cpp
#include <bits/stdc++.h>
using namespace std;

// Books: longest contiguous segment with total time ≤ t
int main() {
    int n; long long t; cin >> n >> t;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long sum = 0; int best = 0;
    for (int l = 0, r = 0; r < n; r++) {
        sum += a[r];
        while (sum > t) sum -= a[l++];
        best = max(best, r - l + 1);
    }
    cout << best << '\n';
}
```

## Problems
- [Books](https://codeforces.com/problemset/problem/279/B) Easy
- [Sum of Two Values](https://cses.fi/problemset/task/1640) Easy
- [Subarray Sums I](https://cses.fi/problemset/task/1660) Easy
- [Playlist](https://cses.fi/problemset/task/1141) Medium
- [Hard Process](https://codeforces.com/problemset/problem/660/C) Medium
- [Sum of Three Values](https://cses.fi/problemset/task/1641) Medium
