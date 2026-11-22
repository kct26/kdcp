#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> even;
        for (int i = 0; i < n; i++) { long long x; cin >> x; if (x % 2 == 0) even.push_back(x); }
        if (even.empty()) { cout << -1 << '\n'; continue; }
        for (size_t i = 0; i < even.size(); i++) cout << even[i] << " \n"[i + 1 == even.size()];
    }
}
