#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int q; cin >> q;
        queue<long long> line;
        while (q--) {
            int type; cin >> type;
            if (type == 1) { long long x; cin >> x; line.push(x); }
            else if (type == 2) { if (!line.empty()) line.pop(); }
            else cout << (line.empty() ? -1 : line.front()) << '\n';
        }
    }
}
