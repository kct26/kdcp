#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int a[MAX], n;
ll x;

void solve() {
    cin >> n >> x;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n, [](int p, int q) {
        ll dp = llabs(p - x), dq = llabs(q - x);
        if (dp != dq) return dp < dq;
        return p < q;
    });
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
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
