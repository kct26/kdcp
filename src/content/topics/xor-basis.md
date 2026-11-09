---
title: XOR Basis (Linear Basis)
summary: Gaussian elimination over GF(2) for subset-XOR questions.
---

Treat numbers as vectors over GF(2). A **basis** of at most B numbers spans exactly the set of XORs of all subsets.

- **Insert**: reduce `x` by basis vectors from the highest bit; if something remains, it's a new basis vector.
- **Max subset XOR**: greedily XOR in basis vectors that increase the value, from high bit to low.
- **Count**: with r basis vectors, there are `2^r` distinct subset XORs, each achieved `2^(n − r)` times.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct XorBasis {
    static const int B = 60;
    ll b[B] = {};
    int rank = 0;
    bool insert(ll x) {
        for (int i = B - 1; i >= 0; i--) if (x >> i & 1) {
            if (!b[i]) { b[i] = x; rank++; return true; }
            x ^= b[i];
        }
        return false;                  // x was already representable
    }
    ll maxXor() {
        ll r = 0;
        for (int i = B - 1; i >= 0; i--) r = max(r, r ^ b[i]);
        return r;
    }
};
```

## Problems
- [(Zero XOR Subset)-less](https://codeforces.com/problemset/problem/1101/G) Medium
- [Mahmoud and Ehab and yet another xor task](https://codeforces.com/problemset/problem/959/F) Hard
- [Maximum Xor Subarray](https://cses.fi/problemset/task/1655) Easy
