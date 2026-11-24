#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int a[MAX], n;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    priority_queue<ll> lo;
    priority_queue<ll, vector<ll>, greater<ll>> hi;
    ll sumLo = 0, sumHi = 0;
    for (int i = 0; i < n; i++) {
        if (lo.empty() || a[i] <= lo.top()) lo.push(a[i]), sumLo += a[i];
        else hi.push(a[i]), sumHi += a[i];
        if (lo.size() > hi.size() + 1) {
            ll v = lo.top(); lo.pop(); sumLo -= v;
            hi.push(v); sumHi += v;
        }
        if (hi.size() > lo.size()) {
            ll v = hi.top(); hi.pop(); sumHi -= v;
            lo.push(v); sumLo += v;
        }
        ll m = lo.top();
        ll cost = (m * (ll)lo.size() - sumLo) + (sumHi - m * (ll)hi.size());
        cout << cost << " \n"[i + 1 == n];
    }
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
