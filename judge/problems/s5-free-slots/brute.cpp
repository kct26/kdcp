#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;
        vector<bool> taken(n + 1, false);
        while (q--) {
            int t; cin >> t;
            if (t == 1) {
                int l, r; cin >> l >> r; int got = -1;
                for (int i = l; i <= r; i++) if (!taken[i]) { got = i; taken[i] = true; break; }
                cout << got << '\n';
            } else { int x; cin >> x; taken[x] = false; }
        }
    }
}
