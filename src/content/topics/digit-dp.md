---
title: Digit DP
summary: Count numbers in [L, R] with a digit property.
---

Count `f(R) − f(L − 1)` where `f(X)` counts valid numbers in `[0, X]`. Build the number digit by digit from the most significant, tracking:

- `pos`: current position;
- `tight`: whether the prefix equals X's prefix (limits the next digit);
- `started`: whether we passed leading zeros (if they matter);
- the problem-specific state (digit sum mod D, previous digit, …).

Memoize only the non-tight states, or include `tight` in the key.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Counting Numbers: count x in [a, b] with no two adjacent equal digits
string s;
long long memo[20][11][2][2];
bool seen[20][11][2][2];

long long go(int pos, int prev, bool tight, bool started) {
    if (pos == (int)s.size()) return 1;
    auto& r = memo[pos][prev][tight][started];
    if (seen[pos][prev][tight][started]) return r;
    seen[pos][prev][tight][started] = true; r = 0;
    int lim = tight ? s[pos] - '0' : 9;
    for (int d = 0; d <= lim; d++) {
        if (started && d == prev) continue;
        bool st = started || d != 0;
        r += go(pos + 1, st ? d : 10, tight && d == lim, st);
    }
    return r;
}
long long f(long long x) {                 // count in [0, x]
    if (x < 0) return 0;
    s = to_string(x); memset(seen, 0, sizeof seen);
    return go(0, 10, true, false);
}
int main() { long long a, b; cin >> a >> b; cout << f(b) - f(a - 1) << '\n'; }
```

## Problems
- [Digit Sum](https://atcoder.jp/contests/dp/tasks/dp_s) Easy
- [Counting Numbers](https://cses.fi/problemset/task/2220) Medium
- [Magic Numbers](https://codeforces.com/problemset/problem/628/D) Hard
