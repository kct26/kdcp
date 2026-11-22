#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        long long pairs = 0;
        for (int l = 0; l < n; l++) {
            long long mid = 0;                   // max strictly between l and r
            for (int r = l + 1; r < n; r++) {
                if (a[l] > mid && a[r] > mid) pairs++;
                mid = max(mid, a[r]);
            }
        }
        cout << pairs << '\n';
    }
}
