---
title: DP + Combinatorics
summary: Count configurations by mixing DP states with binomial coefficients.
---

Many counting problems combine both tools:

- **Grid paths with obstacles**: paths from `(1,1)` to `(i,j)` avoiding blocked cells: sort obstacles, `dp[i] = paths(start → i) − Σ dp[j] · paths(j → i)` over obstacles `j` before `i`. O(k²) instead of O(HW).
- **Partitions / distributions**: `dp[i][j]` = ways using first i items with total j, multiplied by a binomial when items are distinguishable.
- **Inserting elements one by one**: count permutations with a pattern by inserting values in increasing order (Permutation, AtCoder DP T).

```cpp
// Grid 2: H×W grid, N ≤ 3000 walls; count monotone paths mod 1e9+7
// (assumes C(n, k) from the Combinatorics topic)
int main() {
    int H, W, n; cin >> H >> W >> n;
    vector<pair<int,int>> wall(n);
    for (auto& [r, c] : wall) cin >> r >> c;
    sort(wall.begin(), wall.end());
    wall.push_back({H, W});                       // target as last "wall"
    auto paths = [](int r1, int c1, int r2, int c2) {
        return C(r2 - r1 + c2 - c1, r2 - r1);
    };
    vector<ll> dp(n + 1);
    for (int i = 0; i <= n; i++) {
        auto [r, c] = wall[i];
        dp[i] = paths(1, 1, r, c);
        for (int j = 0; j < i; j++) {
            auto [rj, cj] = wall[j];
            if (rj <= r && cj <= c)
                dp[i] = (dp[i] - dp[j] * paths(rj, cj, r, c) % MOD + MOD) % MOD;
        }
    }
    cout << dp[n] << '\n';
}
```

## Problems
- [Grid Paths](https://cses.fi/problemset/task/1638) Easy
- [Grid 2](https://atcoder.jp/contests/dp/tasks/dp_y) Medium
- [Bracket Sequences II](https://cses.fi/problemset/task/2187) Hard
- [Permutation](https://atcoder.jp/contests/dp/tasks/dp_t) Hard
- [Counting Tilings](https://cses.fi/problemset/task/2181) Hard
