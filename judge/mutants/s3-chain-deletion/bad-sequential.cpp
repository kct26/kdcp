// Wrong: removes elements one at a time within a round (later checks see earlier removals).
#include <bits/stdc++.h>
using namespace std;
int main() { ios::sync_with_stdio(false); cin.tie(nullptr); int T; cin >> T; while (T--) { int n; cin >> n;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    vector<int> alive(n), ans(n, -1); iota(alive.begin(), alive.end(), 0);
    for (int r = 1; ; r++) { bool any = false;
        for (size_t j = 1; j + 1 < alive.size(); ) {
            if (a[alive[j]] == llabs(a[alive[j - 1]] - a[alive[j + 1]])) { ans[alive[j]] = r; alive.erase(alive.begin() + j); any = true; }
            else j++; }
        if (!any) break; }
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i + 1 == n]; } }
