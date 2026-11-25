#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        for (int i = 0; i < n; i++) {
            set<long long> smaller;                  // distinct values below a[i]
            for (int j = 0; j < n; j++) if (a[j] < a[i]) smaller.insert(a[j]);
            cout << smaller.size() + 1 << " \n"[i + 1 == n];
        }
    }
}
