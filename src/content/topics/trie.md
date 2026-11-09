---
title: Trie
summary: Prefix tree for strings and the binary trie for XOR queries.
---

A trie stores strings character by character; shared prefixes share nodes. Use it for prefix counting, dictionary DP (Word Combinations), and autocomplete.

**Binary trie**: insert numbers bit by bit from the most significant. To maximize `x ⊕ y` over stored `y`, walk down and prefer the child with the **opposite** bit at each level.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Maximum Xor Subarray: max over prefix XOR pairs
const int B = 30, MAXN = 200'005 * (B + 1);
int ch[MAXN][2], cnt = 1;               // node 0 = root

void insert(int x) {
    int u = 0;
    for (int b = B - 1; b >= 0; b--) {
        int c = x >> b & 1;
        if (!ch[u][c]) ch[u][c] = cnt++;
        u = ch[u][c];
    }
}
int maxXor(int x) {
    int u = 0, r = 0;
    for (int b = B - 1; b >= 0; b--) {
        int c = x >> b & 1;
        if (ch[u][!c]) r |= 1 << b, u = ch[u][!c];
        else u = ch[u][c];
    }
    return r;
}

int main() {
    int n; cin >> n;
    int pre = 0, best = 0;
    insert(0);
    for (int i = 0, x; i < n; i++) {
        cin >> x; pre ^= x;
        best = max(best, maxXor(pre));
        insert(pre);
    }
    cout << best << '\n';
}
```

## Problems
- [Maximum Xor Subarray](https://cses.fi/problemset/task/1655) Easy
- [Vasiliy's Multiset](https://codeforces.com/problemset/problem/706/D) Medium
- [Word Combinations](https://cses.fi/problemset/task/1731) Medium
