#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        long long total = 0;
        for (int l = 0; l < n; l++) {
            long long m1 = a[l], m2 = 0;
            for (int r = l + 1; r < n; r++) {
                if (a[r] > m1) m2 = m1, m1 = a[r]; else m2 = max(m2, a[r]);
                total += m2;
            }
        }
        cout << total << '\n';
    }
}
