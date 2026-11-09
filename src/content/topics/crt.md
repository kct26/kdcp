---
title: Chinese Remainder Theorem
summary: Combine congruences x ≡ aᵢ (mod mᵢ) into one.
---

If the moduli are pairwise coprime, the system `x ≡ aᵢ (mod mᵢ)` has a unique solution modulo `M = Π mᵢ`.

Merge congruences two at a time: this also works for **non-coprime** moduli: `x ≡ a (mod m)` and `x ≡ b (mod n)` is solvable iff `a ≡ b (mod gcd(m, n))`; the merged modulus is `lcm(m, n)`.

Watch for overflow: the lcm can exceed 64 bits quickly, so use `__int128` in intermediate products.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) { x = 1; y = 0; return a; }
    ll x1, y1, g = extgcd(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1; return g;
}

// merge x ≡ a (mod m) with x ≡ b (mod n); returns {x, lcm} or {-1, -1}
pair<ll,ll> crt(ll a, ll m, ll b, ll n) {
    ll p, q, g = extgcd(m, n, p, q);
    if ((b - a) % g) return {-1, -1};
    ll l = m / g * n;
    __int128 t = (__int128)(b - a) / g * p % (n / g);
    ll x = (ll)(((__int128)a + (__int128)m * t) % l);
    return {(x + l) % l, l};
}
```

## Problems
- [Chinese Remainder](https://open.kattis.com/problems/chineseremainder) Easy
- [Chinese Remainder (non-coprime)](https://open.kattis.com/problems/generalchineseremainder) Medium
