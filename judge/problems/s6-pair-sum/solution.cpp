#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int n;
ll M;

void solve() {
    cin >> n >> M;
    map<ll, ll> cnt;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        if (cnt.count(M - x)) ans += cnt[M - x];
        cnt[x]++;
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
