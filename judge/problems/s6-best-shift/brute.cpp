#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;
        vector<int> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        while (q--) {
            int t; cin >> t;
            if (t == 3) {
                map<int, int> c; int best = 0;
                for (int i = 1; i <= n; i++) best = max(best, ++c[b[i] - a[i]]);
                cout << best << '\n';
                continue;
            }
            int i, x; cin >> i >> x;
            if (t == 1) a[i] = x; else b[i] = x;
        }
    }
}
