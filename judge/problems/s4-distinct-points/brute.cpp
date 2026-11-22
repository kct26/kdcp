#include <bits/stdc++.h>
using namespace std;

// try every seat assignment by backtracking over guests (seat 0 = unseated)
int n; vector<long long> r, w; long long best; vector<bool> used;
void go(int i, long long sum) {
    if (i == n) { best = max(best, sum); return; }
    go(i + 1, sum);
    for (long long s = 1; s <= min<long long>(r[i], n); s++) if (!used[s]) {
        used[s] = true; go(i + 1, sum + w[i]); used[s] = false;
    }
}
int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n; r.assign(n, 0); w.assign(n, 0);
        for (auto& x : r) cin >> x;
        for (auto& x : w) cin >> x;
        used.assign(n + 1, false); best = 0; go(0, 0);
        cout << best << '\n';
    }
}
