---
title: Fenwick Tree (BIT) & 2D BIT
summary: Prefix sums with point updates in a dozen lines.
---

A Binary Indexed Tree stores partial sums where index `i` covers `(i − lowbit(i), i]`, with `lowbit(i) = i & -i`. It handles **prefix** queries for invertible operations (sum, XOR).

Tricks:

- **Range update, point query**: add `v` at `l` and `−v` at `r + 1`; the value at `i` is the prefix sum.
- **Counting inversions**: sweep left to right, query how many larger values were inserted.
- **2D BIT**: nest the loops; works for point updates and rectangle sums.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct BIT {                            // 1-indexed
    int n; vector<long long> t;
    BIT(int n) : n(n), t(n + 1, 0) {}
    void add(int i, long long v) { for (; i <= n; i += i & -i) t[i] += v; }
    long long sum(int i) { long long s = 0; for (; i > 0; i -= i & -i) s += t[i]; return s; }
    long long sum(int l, int r) { return sum(r) - sum(l - 1); }
};

struct BIT2D {
    int n; vector<vector<long long>> t;
    BIT2D(int n) : n(n), t(n + 1, vector<long long>(n + 1)) {}
    void add(int x, int y, long long v) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= n; j += j & -j) t[i][j] += v;
    }
    long long sum(int x, int y) {
        long long s = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j) s += t[i][j];
        return s;
    }
};
```

## Problems
- [Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) Easy
- [Fenwick Tree](https://open.kattis.com/problems/fenwick) Easy
- [List Removals](https://cses.fi/problemset/task/1749) Medium
- [Salary Queries](https://cses.fi/problemset/task/1144) Medium
- [Forest Queries II](https://cses.fi/problemset/task/1739) Medium
- [Enemy is weak](https://codeforces.com/problemset/problem/61/E) Medium
