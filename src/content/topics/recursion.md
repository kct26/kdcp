---
title: Recursion & Backtracking
summary: Solve a problem through smaller copies of itself; explore choices and undo them.
---

Every recursive function needs a **base case** and a step that moves toward it. Think of the call tree: its size is the running time.

**Backtracking** builds a solution piece by piece, recursing on each choice and undoing it afterwards. Prune branches as early as possible.

Watch the stack: default limits are ~1–8 MB; recursion depth above ~10⁵–10⁶ may crash.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Generate all permutations of 1..n by backtracking
int n;
vector<int> cur;
vector<bool> used;

void go() {
    if ((int)cur.size() == n) {
        for (int x : cur) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int v = 1; v <= n; v++) if (!used[v]) {
        used[v] = true; cur.push_back(v);
        go();
        used[v] = false; cur.pop_back();   // undo
    }
}

int main() { cin >> n; used.assign(n + 1, false); go(); }
```

## Problems
- [Tower of Hanoi](https://cses.fi/problemset/task/2165) Easy
- [Creating Strings](https://cses.fi/problemset/task/1622) Easy
- [Chessboard and Queens](https://cses.fi/problemset/task/1624) Medium
- [a-Good String](https://codeforces.com/problemset/problem/1385/D) Medium
- [Grid Path Description](https://cses.fi/problemset/task/1625) Hard
