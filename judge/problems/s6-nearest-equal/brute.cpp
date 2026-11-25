#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        while (q--) {
            int t; cin >> t;
            if (t == 1) { int i, x; cin >> i >> x; a[i] = x; continue; }
            map<int, int> last; int D = -1;
            for (int i = 1; i <= n; i++) {
                auto it = last.find(a[i]);
                if (it != last.end() && (D == -1 || i - it->second < D)) D = i - it->second;
                last[a[i]] = i;
            }
            cout << D << '\n';
        }
    }
}
