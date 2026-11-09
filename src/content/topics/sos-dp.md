---
title: SOS DP (Sum over Subsets)
summary: For every mask, aggregate f over all its submasks in O(2ⁿ · n).
---

Naively, `F[mask] = Σ f[sub]` over submasks costs O(3ⁿ). SOS DP handles **one bit at a time**: after processing bit `i`, `F[mask]` includes submasks that differ from `mask` only in bits `≤ i`.

Swap the direction to sum over **supermasks**. Undo it (Möbius transform) by subtracting instead of adding.

Typical questions: "for each x, how many `y` with `x & y = y`?", "how many with `x & y = 0`?" (query the complement), "how many with `x | y = x`?".

```cpp
#include <bits/stdc++.h>
using namespace std;

// Bit Problem: for each x count y with x|y=x, x&y=x, and x&y≠0
int main() {
    const int B = 20;
    int n; cin >> n;
    vector<int> a(n), sub(1 << B, 0), sup(1 << B, 0);
    for (auto& x : a) cin >> x, sub[x]++, sup[x]++;
    for (int i = 0; i < B; i++)
        for (int m = 0; m < (1 << B); m++) {
            if (m >> i & 1) sub[m] += sub[m ^ (1 << i)];   // submasks
            else            sup[m] += sup[m ^ (1 << i)];   // supermasks
        }
    int full = (1 << B) - 1;
    for (int x : a)
        cout << sub[x] << ' ' << sup[x] << ' ' << n - sub[full ^ x] << '\n';
}
```

## Problems
- [Bit Problem](https://cses.fi/problemset/task/1654) Medium
- [Compatible Numbers](https://codeforces.com/problemset/problem/165/E) Medium
- [Jzzhu and Numbers](https://codeforces.com/problemset/problem/449/D) Hard
