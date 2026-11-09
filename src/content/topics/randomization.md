---
title: Randomized Techniques
summary: Random sampling, shuffling and hashing that beat deterministic worst cases.
---

Randomness turns many "worst case" problems into easy ones:

- **Sampling**: if an answer must involve at least half of the elements, a random element is in it with probability ≥ ½. Try ~30 random picks (Ghd, Kuroni and the Punishment).
- **Random shuffling**: shuffle input before inserting into a structure (treaps, expected-linear closest pair).
- **Hashing sets/multisets**: assign each value a random 64-bit number; a multiset's hash is the sum or XOR. Compare subarrays as multisets in O(1).
- **Anti-hack**: seed with time, never use `rand()` (only 15 bits on Windows).

```cpp
#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// random integer in [l, r]
long long rnd(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

// hack-resistant hash for unordered_map
struct SplitMix {
    static uint64_t f(uint64_t x) {
        x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count();
        return f(x + SEED);
    }
};
unordered_map<long long, int, SplitMix> safeMap;
```

## Problems
- [Ghd](https://codeforces.com/problemset/problem/364/D) Hard
- [Kuroni and the Punishment](https://codeforces.com/problemset/problem/1305/F) Hard
- [Sum of Two Values](https://cses.fi/problemset/task/1640) Easy
