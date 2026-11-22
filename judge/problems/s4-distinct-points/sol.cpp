#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<pair<long long,long long>> g(n);        // (r, w)
        for (auto& p : g) cin >> p.first;
        for (auto& p : g) cin >> p.second;
        sort(g.begin(), g.end());
        priority_queue<long long, vector<long long>, greater<>> seated;
        long long total = 0;
        for (auto [r, w] : g) {
            seated.push(w); total += w;
            if ((long long)seated.size() > r) { total -= seated.top(); seated.pop(); }
        }
        cout << total << '\n';
    }
}
