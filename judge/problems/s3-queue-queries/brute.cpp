#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int q; cin >> q;
        vector<long long> v;
        while (q--) {
            int type; cin >> type;
            if (type == 1) { long long x; cin >> x; v.push_back(x); }
            else if (type == 2) { if (!v.empty()) v.erase(v.begin()); }
            else cout << (v.empty() ? -1 : v[0]) << '\n';
        }
    }
}
