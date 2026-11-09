---
title: Divide and Conquer
summary: Split, solve halves recursively, combine.
---

Split the input into halves, solve each recursively, then **combine**. If combining costs O(n), the recurrence `T(n) = 2T(n/2) + O(n)` gives O(n log n).

Merge sort is the template. Its merge step can also count things that cross the middle, e.g. **inversions**: pairs `i < j` with `a[i] > a[j]`.

```cpp
#include <bits/stdc++.h>
using namespace std;

long long inv = 0;

void mergeSort(vector<int>& a, int l, int r) {   // [l, r)
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    mergeSort(a, l, m); mergeSort(a, m, r);
    vector<int> tmp;
    int i = l, j = m;
    while (i < m || j < r) {
        if (j == r || (i < m && a[i] <= a[j])) tmp.push_back(a[i++]);
        else { inv += m - i; tmp.push_back(a[j++]); }   // a[i..m) > a[j]
    }
    copy(tmp.begin(), tmp.end(), a.begin() + l);
}
```

## Problems
- [Painting Fence](https://codeforces.com/problemset/problem/448/C) Medium
- [Masha and a Beautiful Tree](https://codeforces.com/problemset/problem/1741/D) Easy
- [Enemy is weak](https://codeforces.com/problemset/problem/61/E) Medium
- [Minimum Euclidean Distance](https://cses.fi/problemset/task/2194) Hard
