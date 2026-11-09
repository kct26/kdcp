---
title: Inclusion–Exclusion & Möbius
summary: Count by alternating over intersections; Möbius inversion for gcd problems.
---

**Inclusion–exclusion**: `|A₁ ∪ … ∪ A_k| = Σ|Aᵢ| − Σ|Aᵢ ∩ Aⱼ| + …`. Enumerate subsets of conditions with a bitmask; sign is `(−1)^(size+1)`.

**Möbius function** `μ(n)`: 0 if n has a squared prime factor, otherwise `(−1)^(number of prime factors)`. Key fact: `Σ_{d | n} μ(d) = [n = 1]`.

Counting coprime pairs: `#{(i, j) : gcd(aᵢ, aⱼ) = 1} = Σ_d μ(d) · C(cnt[d], 2)`, where `cnt[d]` = how many elements are divisible by d.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MX = 1'000'001;
int mu[MX], cntDiv[MX], freq_[MX];

int main() {
    // linear-ish Möbius sieve
    vector<int> primes; vector<bool> comp(MX);
    mu[1] = 1;
    for (int i = 2; i < MX; i++) {
        if (!comp[i]) primes.push_back(i), mu[i] = -1;
        for (int p : primes) {
            if ((long long)i * p >= MX) break;
            comp[i * p] = true;
            if (i % p == 0) { mu[i * p] = 0; break; }
            mu[i * p] = -mu[i];
        }
    }
    int n; cin >> n;
    for (int i = 0, x; i < n; i++) cin >> x, freq_[x]++;
    for (int d = 1; d < MX; d++) for (int m = d; m < MX; m += d) cntDiv[d] += freq_[m];
    long long ans = 0;
    for (int d = 1; d < MX; d++) ans += (long long)mu[d] * cntDiv[d] * (cntDiv[d] - 1) / 2;
    cout << ans << '\n';                // Counting Coprime Pairs
}
```

## Problems
- [Prime Multiples](https://cses.fi/problemset/task/2185) Easy
- [Christmas Party](https://cses.fi/problemset/task/1717) Medium
- [Counting Coprime Pairs](https://cses.fi/problemset/task/2417) Medium
- [Coprime Subsequences](https://codeforces.com/problemset/problem/803/F) Hard
