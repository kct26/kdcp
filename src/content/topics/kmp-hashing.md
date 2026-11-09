---
title: KMP & String Hashing
summary: Linear-time pattern matching, and comparing substrings in O(1).
---

**Prefix function**: `π[i]` = length of the longest proper prefix of `s[0..i]` that is also a suffix. Matching `p` in `t`: compute `π` of `p + '#' + t`; positions with `π = |p|` are matches. Borders and periods of a string fall out of `π` directly.

**Polynomial hashing**: `h(s) = Σ s[i] · baseⁱ mod M`. Precompute prefix hashes and powers to get any substring's hash in O(1). Use a random base and mod `2⁶¹ − 1` (or two mods) to avoid collisions and anti-hash tests.

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> prefixFunction(const string& s) {
    int n = s.size(); vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

struct Hash {                          // mod 2^61 - 1
    using u64 = uint64_t;
    static constexpr u64 M = (1ULL << 61) - 1;
    static u64 mul(u64 a, u64 b) { __uint128_t c = (__uint128_t)a * b; u64 r = (c & M) + (c >> 61); return r >= M ? r - M : r; }
    vector<u64> h, p;
    Hash(const string& s, u64 B) : h(s.size() + 1), p(s.size() + 1) {
        p[0] = 1;
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = (mul(h[i], B) + s[i]) % M;
            p[i + 1] = mul(p[i], B);
        }
    }
    u64 get(int l, int r) {            // [l, r)
        return (h[r] + M - mul(h[l], p[r - l])) % M;
    }
};
```

## Problems
- [String Matching](https://cses.fi/problemset/task/1753) Easy
- [Finding Borders](https://cses.fi/problemset/task/1732) Easy
- [Finding Periods](https://cses.fi/problemset/task/1733) Medium
- [Password](https://codeforces.com/problemset/problem/126/B) Medium
- [Compress Words](https://codeforces.com/problemset/problem/1200/E) Medium
- [String Matching](https://open.kattis.com/problems/stringmatching) Easy
