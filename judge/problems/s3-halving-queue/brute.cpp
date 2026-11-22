#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<pair<long long,int>> v;
        for (int i = 1; i <= n; i++) { long long x; cin >> x; v.push_back({x, i}); }
        vector<int> log;
        while (!v.empty()) {
            auto [x, id] = v.front(); v.erase(v.begin());
            if (x == 1) log.push_back(id);
            else { v.push_back({x / 2, id}); v.push_back({x - x / 2, id}); }
        }
        for (size_t i = 0; i < log.size(); i++) cout << log[i] << " \n"[i + 1 == log.size()];
    }
}
