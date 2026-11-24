#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int n, q;

void solve() {
    cin >> n >> q;
    set<int> fr;
    for (int i = 1; i <= n; i++) fr.insert(fr.end(), i);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            auto it = fr.lower_bound(l);
            if (it == fr.end() || *it > r) cout << -1 << "\n";
            else {
                cout << *it << "\n";
                fr.erase(it);
            }
        } else {
            int x;
            cin >> x;
            fr.insert(x);
        }
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
