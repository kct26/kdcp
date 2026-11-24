#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int pos[MAX], n;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        pos[v] = i;
    }
    set<int> big = {-1, 0, n + 1, n + 2};
    ll total = 0;
    for (int v = n; v >= 1; v--) {
        int i = pos[v];
        auto it = big.insert(i).first;
        int l1 = *prev(it), l2 = max(0, *prev(prev(it)));
        int r1 = *next(it), r2 = min(n + 1, *next(next(it)));
        ll cnt = 0;
        if (l1 >= 1) cnt += (ll)(l1 - l2) * (r1 - i);
        if (r1 <= n) cnt += (ll)(r2 - r1) * (i - l1);
        total += cnt * v;
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
