---
title: DP with Matrix Exponentiation
summary: Linear recurrences with huge n in O(k³ log n).
---

If the DP transition is **linear and identical at every step** (`v[i+1] = M · v[i]`), then `v[n] = Mⁿ · v[0]`, computed by fast exponentiation.

- Fibonacci: `M = [[1,1],[1,0]]`.
- Paths of length exactly k in a graph: the k-th power of the adjacency matrix (Graph Paths I).
- Replace (+, ×) with (min, +) to get shortest paths with exactly k edges (Graph Paths II).

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;
using Mat = vector<vector<ll>>;

Mat mul(const Mat& A, const Mat& B) {
    int n = A.size();
    Mat C(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) if (A[i][k])
            for (int j = 0; j < n; j++) C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}
Mat power(Mat A, ll e) {
    int n = A.size(); Mat R(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) R[i][i] = 1;
    for (; e; e >>= 1, A = mul(A, A)) if (e & 1) R = mul(R, A);
    return R;
}

int main() {                           // n-th Fibonacci number
    ll n; cin >> n;
    cout << power({{1, 1}, {1, 0}}, n)[0][1] << '\n';
}
```

## Problems
- [Fibonacci Numbers](https://cses.fi/problemset/task/1722) Easy
- [Throwing Dice](https://cses.fi/problemset/task/1096) Medium
- [Graph Paths I](https://cses.fi/problemset/task/1723) Medium
- [Walk](https://atcoder.jp/contests/dp/tasks/dp_r) Medium
- [Graph Paths II](https://cses.fi/problemset/task/1724) Hard
- [Plant](https://codeforces.com/problemset/problem/185/A) Easy
