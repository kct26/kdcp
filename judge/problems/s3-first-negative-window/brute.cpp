#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        for (int l = 0; l + k <= n; l++) {
            long long ans = 0;
            for (int i = l; i < l + k; i++) if (a[i] < 0) { ans = a[i]; break; }
            cout << ans << " \n"[l + k == n];
        }
    }
}
