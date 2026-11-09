---
title: Meet in the Middle
summary: Split the input in half, enumerate each side, and combine.
---

When n ≈ 40, `2⁴⁰` is too large but `2²⁰ ≈ 10⁶` is fine. Split items into two halves, enumerate all subset results of each half, then **combine** with sorting + two pointers, binary search, or a hash map.

Example: count subsets with sum exactly `x`: enumerate sums of the left half into a sorted list, and for each right-half sum `s`, count how many left sums equal `x − s`.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> sums(const vector<ll>& a) {
    vector<ll> r = {0};
    for (ll x : a) {                   // merge keeps r sorted
        vector<ll> with(r.size());
        for (size_t i = 0; i < r.size(); i++) with[i] = r[i] + x;
        vector<ll> m; merge(r.begin(), r.end(), with.begin(), with.end(), back_inserter(m));
        r = move(m);
    }
    return r;
}

int main() {
    int n; ll x; cin >> n >> x;
    vector<ll> a(n);
    for (auto& v : a) cin >> v;
    auto A = sums(vector<ll>(a.begin(), a.begin() + n / 2));
    auto B = sums(vector<ll>(a.begin() + n / 2, a.end()));
    ll ans = 0;
    for (ll s : A) {
        auto [lo, hi] = equal_range(B.begin(), B.end(), x - s);
        ans += hi - lo;
    }
    cout << ans << '\n';
}
```

## Problems
- [Meet in the Middle](https://cses.fi/problemset/task/1628) Medium
- [Maximum Subsequence](https://codeforces.com/problemset/problem/888/E) Medium
- [Apple Division](https://cses.fi/problemset/task/1623) Easy
