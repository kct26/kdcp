#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<pair<long long,long long>> t(n);       // (deadline, points)
        for (auto& [d, w] : t) cin >> d >> w;
        sort(t.begin(), t.end());
        priority_queue<long long, vector<long long>, greater<>> chosen;
        long long total = 0;
        for (auto [d, w] : t) {
            chosen.push(w); total += w;
            if ((long long)chosen.size() > d) { total -= chosen.top(); chosen.pop(); }
        }
        cout << total << '\n';
    }
}
