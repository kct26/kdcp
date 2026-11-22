#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        vector<int> alive(n), ans(n, -1);
        iota(alive.begin(), alive.end(), 0);
        for (int r = 1; ; r++) {
            vector<int> keep; bool any = false;
            for (size_t j = 0; j < alive.size(); j++) {
                bool mark = j > 0 && j + 1 < alive.size() &&
                            a[alive[j]] == llabs(a[alive[j - 1]] - a[alive[j + 1]]);
                if (mark) { ans[alive[j]] = r; any = true; } else keep.push_back(alive[j]);
            }
            if (!any) break;
            alive = keep;
        }
        for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i + 1 == n];
    }
}
