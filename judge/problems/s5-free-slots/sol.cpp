#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;
        set<int> freeSpots;
        for (int i = 1; i <= n; i++) freeSpots.insert(freeSpots.end(), i);
        while (q--) {
            int t; cin >> t;
            if (t == 1) {
                int l, r; cin >> l >> r;
                auto it = freeSpots.lower_bound(l);
                if (it == freeSpots.end() || *it > r) cout << -1 << '\n';
                else { cout << *it << '\n'; freeSpots.erase(it); }
            } else {
                int x; cin >> x; freeSpots.insert(x);
            }
        }
    }
}
