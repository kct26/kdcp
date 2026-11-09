---
title: Bit Manipulation
summary: Treat integers as sets of bits. Fast, compact, and everywhere.
---

| Expression | Meaning |
| --- | --- |
| `x >> i & 1` | i-th bit of x |
| `x \| (1 << i)` | set bit i |
| `x & ~(1 << i)` | clear bit i |
| `x & -x` | lowest set bit |
| `x & (x - 1)` | remove lowest set bit |
| `__builtin_popcount(x)` | number of set bits (`ll` suffix for 64-bit) |

**XOR facts**: `a ^ a = 0`, `a ^ 0 = a`, XOR is associative and commutative, so prefix XORs work exactly like prefix sums.

**Subset enumeration**: a mask `0 … 2ⁿ−1` describes a subset of n items.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Apple Division: split n ≤ 20 weights into two groups, minimize difference
int main() {
    int n; cin >> n;
    vector<long long> p(n);
    for (auto& x : p) cin >> x;
    long long total = accumulate(p.begin(), p.end(), 0LL), best = LLONG_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long s = 0;
        for (int i = 0; i < n; i++) if (mask >> i & 1) s += p[i];
        best = min(best, llabs(total - 2 * s));
    }
    cout << best << '\n';
}
```

## Problems
- [Raising Bacteria](https://codeforces.com/problemset/problem/579/A) Easy
- [Apple Division](https://cses.fi/problemset/task/1623) Easy
- [Petr and a Combination Lock](https://codeforces.com/problemset/problem/1097/B) Easy
- [Gray Code](https://cses.fi/problemset/task/2205) Medium
- [Range Xor Queries](https://cses.fi/problemset/task/1650) Easy
