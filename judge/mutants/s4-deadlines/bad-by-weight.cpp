// Wrong: takes tasks by decreasing points while fewer than d tasks are taken.
#include <bits/stdc++.h>
using namespace std;
int main() { ios::sync_with_stdio(false); cin.tie(nullptr); int T; cin >> T; while (T--) { int n; cin >> n;
    vector<pair<long long,long long>> t(n); for (auto& [w, d] : t) cin >> d >> w;
    sort(t.rbegin(), t.rend()); long long total = 0, taken = 0;
    for (auto [w, d] : t) if (taken < d) taken++, total += w;
    cout << total << '\n'; } }
