#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<int> p(m, 0);                    // column sums of the rows read so far
        map<vector<int>, long long> cnt;
        vector<int> key(max(0, m - 1), 0);
        cnt[key] = 1;                           // the empty prefix
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) { int x; cin >> x; p[j] += x; }
            for (int j = 1; j < m; j++) key[j - 1] = p[j] - p[0];
            ans += cnt[key]++;
        }
        cout << ans << '\n';
    }
}
