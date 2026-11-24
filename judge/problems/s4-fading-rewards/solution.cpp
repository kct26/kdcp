#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int n, k;

void solve() {
    cin >> n >> k;
    priority_queue<pair<ll,ll>> pq;
    for (int i = 0; i < n; i++) {
        ll b, d;
        cin >> b >> d;
        pq.push({b, d});
    }
    ll total = 0;
    while (k--) {
        auto [v, d] = pq.top();
        pq.pop();
        total += v;
        pq.push({max(0LL, v - d), d});
    }
    cout << total << "\n";
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
