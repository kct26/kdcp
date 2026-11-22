#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; long long x; cin >> n >> x;
        vector<long long> a(n);
        for (auto& v : a) cin >> v;
        sort(a.begin(), a.end(), [&](long long p, long long q) {
            long long dp = llabs(p - x), dq = llabs(q - x);
            return dp != dq ? dp < dq : p < q;
        });
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
    }
}
