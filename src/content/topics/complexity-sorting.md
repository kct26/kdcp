---
title: Complexity, Vector & Sorting
summary: Estimate running time before you code, then lean on vector and sort.
---

## Estimating complexity

A judge executes roughly **10⁸ simple operations per second**. Read the constraints first: they tell you which complexity is expected.

| n ≤ | Target |
| --- | --- |
| 10 | O(n!) |
| 20 | O(2ⁿ · n) |
| 500 | O(n³) |
| 5 000 | O(n²) |
| 10⁶ | O(n log n) |
| 10⁹+ | O(log n) or O(1) |

## vector

`std::vector` is a dynamic array: O(1) random access, amortized O(1) `push_back`. Prefer it over raw arrays.

## Sorting

`std::sort` runs in O(n log n). Pass a comparator (a strict weak ordering) for custom orders. Sorting is often the first step that unlocks greedy, two pointers, or binary search.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<pair<int,int>> a(n);           // (value, index)
    for (int i = 0; i < n; i++) cin >> a[i].first, a[i].second = i;

    // sort by value desc, ties by index asc
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        if (x.first != y.first) return x.first > y.first;
        return x.second < y.second;
    });

    // remove duplicates from a sorted vector
    vector<int> v = {3, 1, 3, 2, 1};
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());   // {1, 2, 3}
}
```

## Problems
- [Distinct Numbers](https://cses.fi/problemset/task/1621) Easy
- [Apartments](https://cses.fi/problemset/task/1084) Easy
- [Ferris Wheel](https://cses.fi/problemset/task/1090) Easy
- [Stick Lengths](https://cses.fi/problemset/task/1074) Easy
- [Restaurant Customers](https://cses.fi/problemset/task/1619) Medium
- [Tasks and Deadlines](https://cses.fi/problemset/task/1630) Medium
