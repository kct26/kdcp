#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n, q, k; cin >> n >> q >> k;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        while (q--) {
            int t; cin >> t;
            if (t == 1) { long long x, y; cin >> x >> y; *find(a.begin(), a.end(), x) = y; }
            else cin >> k;
            vector<long long> s = a; sort(s.rbegin(), s.rend());
            long long sum = 0; for (int i = 0; i < k; i++) sum += s[i];
            cout << sum << '\n';
        }
    }
}
