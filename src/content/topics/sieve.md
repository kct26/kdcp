---
title: Sieve of Eratosthenes
summary: All primes up to N, plus smallest-prime-factor tables for fast factorization.
---

Mark every multiple of each prime as composite, starting from `p²`. What remains unmarked is prime.

Storing the **smallest prime factor** `spf[x]` instead of a boolean lets you factorize any `x ≤ N` in O(log x) by repeatedly dividing by `spf[x]`.

A divisor-style sieve (loop `i` and add to all multiples) computes divisor counts/sums for all numbers in O(N log N).

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1'000'000;
int spf[N + 1];

void sieve() {
    for (int i = 2; i <= N; i++) if (!spf[i])
        for (int j = i; j <= N; j += i) if (!spf[j]) spf[j] = i;
}

vector<int> factorize(int x) {        // prime factors with multiplicity
    vector<int> f;
    while (x > 1) f.push_back(spf[x]), x /= spf[x];
    return f;
}
```

## Problems
- [Almost Prime](https://codeforces.com/problemset/problem/26/A) Easy
- [T-primes](https://codeforces.com/problemset/problem/230/B) Easy
- [Counting Divisors](https://cses.fi/problemset/task/1713) Easy
- [Common Divisors](https://cses.fi/problemset/task/1081) Medium
- [Colliders](https://codeforces.com/problemset/problem/154/B) Medium
- [Prime Sieve](https://open.kattis.com/problems/primesieve) Easy
