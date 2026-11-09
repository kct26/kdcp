---
title: Suffix Array
summary: Sort all suffixes of a string; add LCP for substring problems.
---

The suffix array lists the starting positions of all suffixes in sorted order. Build it by **prefix doubling**: sort by the first `2ᵏ` characters using the ranks of the first `2ᵏ⁻¹`.

The **LCP array** (`lcp[i]` = longest common prefix of suffixes `sa[i]` and `sa[i+1]`) is computed in O(n) with Kasai's algorithm.

Applications:

- Number of distinct substrings = `n(n+1)/2 − Σ lcp`.
- Longest repeated substring = `max lcp`.
- Pattern search by binary search over the suffix array.

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> suffixArray(string s) {
    s += '$';
    int n = s.size();
    vector<int> sa(n), rk(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; i++) rk[i] = s[i];
    for (int k = 1;; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rk[a] != rk[b]) return rk[a] < rk[b];
            return rk[(a + k) % n] < rk[(b + k) % n];
        };
        sort(sa.begin(), sa.end(), cmp);       // O(n log² n), fine for 2e5
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rk = tmp;
        if (rk[sa[n - 1]] == n - 1) break;
    }
    sa.erase(sa.begin());                      // drop the '$' suffix
    return sa;
}

vector<int> lcpArray(const string& s, const vector<int>& sa) {   // Kasai
    int n = s.size(); vector<int> rk(n), lcp(max(0, n - 1));
    for (int i = 0; i < n; i++) rk[sa[i]] = i;
    for (int i = 0, h = 0; i < n; i++) {
        if (h) h--;
        if (rk[i] == n - 1) { h = 0; continue; }
        int j = sa[rk[i] + 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        lcp[rk[i]] = h;
    }
    return lcp;
}
```

## Problems
- [Suffix Sorting](https://open.kattis.com/problems/suffixsorting) Easy
- [Distinct Substrings](https://cses.fi/problemset/task/2105) Medium
- [Repeating Substring](https://cses.fi/problemset/task/2106) Medium
- [String Matching](https://cses.fi/problemset/task/1753) Easy
