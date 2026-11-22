#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int n = s.size(), best = 0;
        for (int l = 0; l < n; l++) {
            int bal = 0;
            for (int r = l; r < n; r++) {
                bal += s[r] == '(' ? 1 : -1;
                if (bal < 0) break;
                if (bal == 0) best = max(best, r - l + 1);
            }
        }
        cout << best << '\n';
    }
}
