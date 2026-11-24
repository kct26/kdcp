#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int a[MAX], n, q, k;
multiset<int> top, rest;
ll sum;

void rebalance() {
    while ((int)top.size() > k) {
        auto it = top.begin();
        sum -= *it; rest.insert(*it); top.erase(it);
    }
    while ((int)top.size() < k) {
        auto it = prev(rest.end());
        sum += *it; top.insert(*it); rest.erase(it);
    }
    while (!top.empty() && !rest.empty() && *prev(rest.end()) > *top.begin()) {
        int u = *top.begin(), v = *prev(rest.end());
        top.erase(top.begin()); rest.erase(prev(rest.end()));
        top.insert(v); rest.insert(u);
        sum += v - u;
    }
}

void solve() {
    cin >> n >> q >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n, greater<int>());
    top.clear(); rest.clear(); sum = 0;
    for (int i = 0; i < n; i++) {
        if (i < k) top.insert(a[i]), sum += a[i];
        else rest.insert(a[i]);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            auto it = rest.find(x);
            if (it != rest.end()) rest.erase(it);
            else {
                top.erase(top.find(x));
                sum -= x;
            }
            rest.insert(y);
        } else {
            cin >> k;
        }
        rebalance();
        cout << sum << "\n";
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
