#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        vector<int> st = {-1};             // bottom = boundary before the current stretch
        int best = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(') { st.push_back(i); continue; }
            st.pop_back();
            if (st.empty()) st.push_back(i);   // unmatched ')' becomes the new boundary
            else best = max(best, i - st.back());
        }
        cout << best << '\n';
    }
}
