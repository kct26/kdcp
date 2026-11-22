#include <bits/stdc++.h>
using namespace std;

// try every subset; a subset is doable iff, sorted by deadline, the j-th task has deadline >= j
int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> d(n), w(n);
        for (int i = 0; i < n; i++) cin >> d[i] >> w[i];
        long long best = 0;
        for (int m = 0; m < (1 << n); m++) {
            vector<long long> ds; long long s = 0;
            for (int i = 0; i < n; i++) if (m >> i & 1) ds.push_back(d[i]), s += w[i];
            sort(ds.begin(), ds.end());
            bool ok = true;
            for (size_t j = 0; j < ds.size(); j++) if (ds[j] < (long long)j + 1) ok = false;
            if (ok) best = max(best, s);
        }
        cout << best << '\n';
    }
}
