#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        for (int i = 1; i <= n; i++) {
            long long best = LLONG_MAX;
            for (int c = 0; c < i; c++) {           // the optimum is at one of the points
                long long s = 0;
                for (int j = 0; j < i; j++) s += llabs(a[j] - a[c]);
                best = min(best, s);
            }
            cout << best << " \n"[i == n];
        }
    }
}
