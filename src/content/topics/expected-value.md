---
title: Expected Value
summary: Linearity of expectation and expectation DP.
---

**Linearity of expectation**: `E[X + Y] = E[X] + E[Y]`, even when X and Y are dependent. Break a complicated quantity into a sum of indicator variables and add up their probabilities.

**Expectation DP**: `E[state] = Σ P(move) · (cost + E[next state])`. If a state can loop to itself, move that term to the left side and solve for `E[state]`.

Example: on a random-order deletion game on a tree, node `v` is chosen directly iff it is picked before all its ancestors: probability `1 / depth(v)`. The answer is `Σ 1 / depth(v)`.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Sushi: dp[a][b][c] = expected moves with a plates of 1, b of 2, c of 3 pieces
int n;
double memo[301][301][301];
bool done_[301][301][301];

double E(int a, int b, int c) {
    if (a + b + c == 0) return 0;
    if (done_[a][b][c]) return memo[a][b][c];
    int s = a + b + c;
    double r = n;                                    // expected tries to hit a non-empty plate
    if (a) r += a * E(a - 1, b, c);
    if (b) r += b * E(a + 1, b - 1, c);
    if (c) r += c * E(a, b + 1, c - 1);
    done_[a][b][c] = true;
    return memo[a][b][c] = r / s;
}
```

## Problems
- [Little Pony and Expected Maximum](https://codeforces.com/problemset/problem/453/A) Easy
- [Candy Lottery](https://cses.fi/problemset/task/1727) Easy
- [Moving Robots](https://cses.fi/problemset/task/1726) Medium
- [Sushi](https://atcoder.jp/contests/dp/tasks/dp_j) Medium
- [Game on Tree](https://codeforces.com/problemset/problem/280/C) Medium
