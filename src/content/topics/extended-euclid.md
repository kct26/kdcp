---
title: Extended Euclidean Algorithm
summary: Solve ax + by = gcd(a, b), modular inverses for any modulus.
---

Besides `g = gcd(a, b)`, the extended algorithm returns `x, y` with `a·x + b·y = g`.

- **Linear Diophantine** `a·x + b·y = c` has a solution iff `g | c`. Scale the base solution by `c / g`; all solutions are `x + k·(b/g)`, `y − k·(a/g)`.
- **Modular inverse** of `a` mod `m` exists iff `gcd(a, m) = 1`: it's the `x` from `a·x + m·y = 1`.
- **Linear congruence** `a·x ≡ c (mod m)`: divide everything by g, then multiply by the inverse.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) { x = 1; y = 0; return a; }
    ll x1, y1, g = extgcd(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
}

ll modinv(ll a, ll m) {                 // -1 if no inverse
    ll x, y;
    if (extgcd(a, m, x, y) != 1) return -1;
    return (x % m + m) % m;
}
```

## Problems
- [Line](https://codeforces.com/problemset/problem/7/C) Easy
- [Modular Arithmetic](https://open.kattis.com/problems/modulararithmetic) Medium
- [Exponentiation II](https://cses.fi/problemset/task/1712) Easy
