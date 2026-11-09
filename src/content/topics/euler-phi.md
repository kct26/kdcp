---
title: Euler's Totient
summary: φ(n) counts integers ≤ n coprime to n and powers up modular arithmetic.
---

`φ(n) = n · Π (1 − 1/p)` over distinct primes `p | n`.

Facts:

- **Euler's theorem**: `a^φ(m) ≡ 1 (mod m)` when `gcd(a, m) = 1`. Fermat's little theorem is the case `m` prime.
- **Exponent reduction**: `a^(b^c) mod p = a^(b^c mod (p − 1)) mod p` for prime p, `a` not divisible by p.
- `Σ_{d | n} φ(d) = n`; so `Σ_{i=1..n} gcd(i, n) = Σ_{d | n} d · φ(n / d)`.

```cpp
#include <bits/stdc++.h>
using namespace std;

long long phi(long long n) {
    long long r = n;
    for (long long p = 2; p * p <= n; p++) if (n % p == 0) {
        while (n % p == 0) n /= p;
        r -= r / p;
    }
    if (n > 1) r -= r / n;
    return r;
}

vector<int> phiSieve(int N) {
    vector<int> ph(N + 1);
    iota(ph.begin(), ph.end(), 0);
    for (int i = 2; i <= N; i++) if (ph[i] == i)          // i is prime
        for (int j = i; j <= N; j += i) ph[j] -= ph[j] / i;
    return ph;
}
```

## Problems
- [Exponentiation II](https://cses.fi/problemset/task/1712) Easy
- [Divisor Analysis](https://cses.fi/problemset/task/2182) Medium
- [Sum of Divisors](https://cses.fi/problemset/task/1082) Medium
