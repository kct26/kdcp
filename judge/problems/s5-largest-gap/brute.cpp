#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        long long n; int q; cin >> n >> q;
        vector<long long> m = {0, n};
        while (q--) {
            int t; long long x; cin >> t >> x;
            if (t == 1) m.push_back(x); else m.erase(find(m.begin(), m.end(), x));
            vector<long long> s = m; sort(s.begin(), s.end());
            long long best = 0;
            for (size_t i = 1; i < s.size(); i++) best = max(best, s[i] - s[i - 1]);
            cout << best << '\n';
        }
    }
}
