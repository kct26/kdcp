#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int a[MAX], n;

void solve() {
    cin >> n;
    vector<int> even;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 2 == 0) even.push_back(a[i]);
    }
    if (even.empty()) {
        cout << -1 << "\n";
        return;
    }
    for (int i = 0; i < (int)even.size(); i++) cout << even[i] << " \n"[i + 1 == (int)even.size()];
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
