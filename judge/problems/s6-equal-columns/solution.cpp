#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int n, m;

void solve() {
    cin >> n >> m;
    vector<int> p(m, 0), key(max(0, m - 1), 0);
    map<vector<int>, ll> cnt;
    cnt[key] = 1;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            p[j] += x;
        }
        for (int j = 1; j < m; j++) key[j - 1] = p[j] - p[0];
        ans += cnt[key];
        cnt[key]++;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    int test = 1;
    cin >> test;
    while (test--) {
        solve();
    }
    return 0;
}
