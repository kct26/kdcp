---
title: Heap (priority_queue)
summary: Always know the current best element in O(log n).
---

A binary heap keeps the maximum (or minimum) at the top. In C++, `priority_queue<T>` is a max-heap; use `greater<T>` for a min-heap.

Typical uses: Dijkstra, merging sorted lists, scheduling, and **greedy with regret**: take items greedily, and when a constraint breaks, drop the worst item taken so far.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Potions: drink as many as possible while health never drops below 0
int main() {
    int n; cin >> n;
    long long hp = 0;
    priority_queue<long long, vector<long long>, greater<>> taken; // min-heap
    for (int i = 0; i < n; i++) {
        long long x; cin >> x;
        hp += x; taken.push(x);
        if (hp < 0) { hp -= taken.top(); taken.pop(); }   // undo the worst
    }
    cout << taken.size() << '\n';
}
```

## Problems
- [Potions (Hard Version)](https://codeforces.com/problemset/problem/1526/C2) Easy
- [Room Allocation](https://cses.fi/problemset/task/1164) Medium
- [Movie Festival II](https://cses.fi/problemset/task/1632) Medium
- [Least Cost Bracket Sequence](https://codeforces.com/problemset/problem/3/D) Hard
- [Buy Low Sell High](https://codeforces.com/problemset/problem/865/D) Hard
