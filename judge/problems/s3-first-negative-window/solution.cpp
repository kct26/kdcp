#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int a[MAX], n, k;

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    deque<int> neg;
    vector<int> res;
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) neg.push_back(i);
        if (!neg.empty() && neg.front() <= i - k) neg.pop_front();
        if (i >= k - 1) res.push_back(neg.empty() ? 0 : a[neg.front()]);
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
