#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int a[MAX], n;

void solve() {
    cin >> n;
    queue<pair<int,int>> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        q.push({a[i], i});
    }
    vector<int> res;
    while (!q.empty()) {
        auto [x, id] = q.front();
        q.pop();
        if (x == 1) res.push_back(id);
        else {
            q.push({x / 2, id});
            q.push({(x + 1) / 2, id});
        }
    }
    for (int i = 0; i < (int)res.size(); i++) cout << res[i] << " \n"[i + 1 == (int)res.size()];
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
