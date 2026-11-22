#include <bits/stdc++.h>
using namespace std;

// enumerate every string of each length in dictionary order and keep the valid ones
int main() {
    vector<string> codes;
    for (int len = 1; (int)codes.size() < 2000; len++) {
        int total = 1; for (int i = 0; i < len; i++) total *= 3;
        for (int m = 0; m < total; m++) {
            string s(len, '1'); int x = m;
            for (int i = len - 1; i >= 0; i--) { s[i] = char('1' + x % 3); x /= 3; }
            bool ok = true;
            for (int i = 1; i < len; i++) if (s[i] == s[i - 1]) ok = false;
            if (ok) codes.push_back(s);
        }
    }
    int T; cin >> T;
    while (T--) { int k; cin >> k; cout << codes[k - 1] << '\n'; }
}
