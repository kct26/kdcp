#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        bool changed = true;
        while (changed) {
            changed = false;
            for (size_t i = 0; i + 1 < s.size(); i++)
                if (s[i] == s[i + 1]) { s.erase(i, 2); changed = true; break; }
        }
        cout << (s.empty() ? "-" : s) << '\n';
    }
}
