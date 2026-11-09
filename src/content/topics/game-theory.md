---
title: Game Theory
summary: Winning/losing positions, Nim, and Sprague–Grundy.
---

In a finite two-player game with no draws, a position is **winning** iff some move leads to a **losing** position. Compute it bottom-up.

**Nim**: piles `a₁ … aₙ`, take any positive amount from one pile. The first player wins iff `a₁ ⊕ a₂ ⊕ … ⊕ aₙ ≠ 0`.

**Sprague–Grundy**: every impartial game is equivalent to a Nim pile of size `g = mex{ g(next) }`. The sum of independent games has Grundy value equal to the XOR of the parts.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Grundy values when you may remove 1..3 sticks (Nim Game II style)
int main() {
    int n = 20;
    vector<int> g(n + 1, 0);
    for (int x = 1; x <= n; x++) {
        set<int> s;
        for (int k = 1; k <= 3 && k <= x; k++) s.insert(g[x - k]);
        int mex = 0;
        while (s.count(mex)) mex++;
        g[x] = mex;                        // turns out g[x] = x % 4
    }
    for (int x = 0; x <= n; x++) cout << g[x] << ' ';
}
```

## Problems
- [Stones](https://atcoder.jp/contests/dp/tasks/dp_k) Easy
- [Stick Game](https://cses.fi/problemset/task/1729) Easy
- [Nim Game I](https://cses.fi/problemset/task/1730) Easy
- [Nim Game II](https://cses.fi/problemset/task/1098) Medium
- [Stair Game](https://cses.fi/problemset/task/1099) Medium
- [Grundy's Game](https://cses.fi/problemset/task/2207) Hard
