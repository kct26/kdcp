#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int n;
ll K;

void solve() {
    cin >> n >> K;
    priority_queue<pair<ll,ll>> pq;
    ll offset = 0;
    for (int i = 0; i < n; i++) {
        ll a, b, x;
        cin >> a >> b >> x;
        pq.push({a - offset, b});
        offset += x;
        int removed = 0;
        while (!pq.empty() && pq.top().first + offset >= K) {
            offset += pq.top().second;
            pq.pop();
            removed++;
        }
        cout << removed << " \n"[i + 1 == n];
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
