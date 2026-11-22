#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        map<int, char> s;
        for (int i = 0; i < n; i++) {
            string t; int k; cin >> t >> k;
            while (k--) { int x; cin >> x; for (size_t j = 0; j < t.size(); j++) s[x + j] = t[j]; }
        }
        string out;
        for (auto& [p, c] : s) out += c;
        cout << out << '\n';
    }
}
