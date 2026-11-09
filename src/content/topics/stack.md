---
title: Stack
summary: Last in, first out and the monotonic stack trick.
---

A stack supports `push`, `pop` and `top` in O(1). Classic uses: bracket matching, expression evaluation, iterative DFS.

## Monotonic stack

To find, for every element, the **nearest smaller value to the left**, keep a stack of indices whose values are increasing. Before pushing `i`, pop everything `≥ a[i]`: those can never be an answer for anything to the right. Each index is pushed and popped once, so the whole pass is O(n).

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n), left(n);
    for (auto& x : a) cin >> x;

    stack<int> st;                        // indices, values increasing
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    for (int x : left) cout << x + 1 << ' ';   // 1-indexed, 0 = none
}
```

## Problems
- [Nearest Smaller Values](https://cses.fi/problemset/task/1645) Easy
- [Longest Regular Bracket Sequence](https://codeforces.com/problemset/problem/5/C) Medium
- [Alternating Current](https://codeforces.com/problemset/problem/343/B) Medium
- [Mike and Feet](https://codeforces.com/problemset/problem/547/B) Medium
- [Maximum Xor Secondary](https://codeforces.com/problemset/problem/280/B) Medium
