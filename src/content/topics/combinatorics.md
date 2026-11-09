---
title: Combinatorics
summary: Counting with factorials, binomials and modular inverses.
---

Answers are usually requested **mod p** (a prime like 10⁹+7). Division is multiplication by the modular inverse: by Fermat, `a⁻¹ ≡ a^(p−2) (mod p)`.

Precompute `fact[i]` and `inv_fact[i]`, then `C(n, k) = fact[n] · inv_fact[k] · inv_fact[n−k]`.

Core identities:

- **Stars and bars**: ways to put n identical balls into k boxes: `C(n + k − 1, k − 1)`.
- **Catalan numbers**: balanced bracket sequences of length 2n: `C(2n, n) / (n + 1)`.
- **Derangements**: `D(n) = (n − 1)(D(n − 1) + D(n − 2))`.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;
const int N = 2'000'001;
ll f[N], inv_f[N];

ll power(ll b, ll e) { ll r = 1; b %= MOD; for (; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD; return r; }

void init() {
    f[0] = 1;
    for (int i = 1; i < N; i++) f[i] = f[i - 1] * i % MOD;
    inv_f[N - 1] = power(f[N - 1], MOD - 2);
    for (int i = N - 1; i > 0; i--) inv_f[i - 1] = inv_f[i] * i % MOD;
}
ll C(int n, int k) { return (k < 0 || k > n) ? 0 : f[n] * inv_f[k] % MOD * inv_f[n - k] % MOD; }
```

## Problems
- [Exponentiation](https://cses.fi/problemset/task/1095) Easy
- [Binomial Coefficients](https://cses.fi/problemset/task/1079) Easy
- [Creating Strings II](https://cses.fi/problemset/task/1715) Easy
- [Distributing Apples](https://cses.fi/problemset/task/1716) Easy
- [Christmas Party](https://cses.fi/problemset/task/1717) Medium
- [Bracket Sequences I](https://cses.fi/problemset/task/2064) Medium
- [Beautiful Numbers](https://codeforces.com/problemset/problem/300/C) Medium
- [Count the Arrays](https://codeforces.com/problemset/problem/1312/D) Medium
