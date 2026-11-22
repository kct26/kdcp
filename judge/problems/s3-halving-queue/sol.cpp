#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        queue<pair<long long,int>> q;           // (number, label)
        for (int i = 1; i <= n; i++) { long long x; cin >> x; q.push({x, i}); }
        vector<int> log;
        while (!q.empty()) {
            auto [x, id] = q.front(); q.pop();
            if (x == 1) log.push_back(id);
            else { q.push({x / 2, id}); q.push({(x + 1) / 2, id}); }
        }
        for (size_t i = 0; i < log.size(); i++) cout << log[i] << " \n"[i + 1 == log.size()];
    }
}
