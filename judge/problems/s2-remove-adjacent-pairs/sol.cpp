#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        string s, st; cin >> s;
        for (char c : s) {
            if (!st.empty() && st.back() == c) st.pop_back();
            else st.push_back(c);
        }
        cout << (st.empty() ? "-" : st) << '\n';
    }
}
