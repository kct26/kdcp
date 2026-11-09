---
title: Queue & Deque
summary: FIFO order, and the sliding-window minimum with a monotonic deque.
---

`queue` gives FIFO order (BFS, simulations). `deque` allows O(1) push/pop at **both** ends.

## Sliding window minimum

Keep a deque of indices whose values are increasing. When a new element arrives, pop from the back everything larger than it; pop from the front indices that left the window. The front is always the minimum of the current window.

```cpp
#include <bits/stdc++.h>
using namespace std;

// min of every window of length k
vector<int> slidingMin(const vector<int>& a, int k) {
    deque<int> dq;                        // indices, values increasing
    vector<int> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}
```

## Problems
- [Josephus Problem I](https://cses.fi/problemset/task/2162) Easy
- [Permutation Minimization by Deque](https://codeforces.com/problemset/problem/1579/E1) Easy
- [Array Optimization by Deque](https://codeforces.com/problemset/problem/1579/E2) Medium
- [Maximum Subarray Sum II](https://cses.fi/problemset/task/1644) Medium
- [Candies](https://atcoder.jp/contests/dp/tasks/dp_m) Medium
