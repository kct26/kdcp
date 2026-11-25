#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> g(n, vector<int>(m));
        for (auto& r : g) for (auto& x : r) cin >> x;
        long long ans = 0;
        for (int l = 0; l < n; l++) {
            vector<int> s(m, 0);
            for (int r = l; r < n; r++) {
                for (int j = 0; j < m; j++) s[j] += g[r][j];
                bool ok = true;
                for (int j = 1; j < m; j++) if (s[j] != s[0]) ok = false;
                ans += ok;
            }
        }
        cout << ans << '\n';
    }
}
