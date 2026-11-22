#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> st;
        for (int i = 0; i < n; i++) {
            long long x; cin >> x;
            bool alive = true;
            while (alive && x < 0 && !st.empty() && st.back() > 0) {
                if (st.back() < -x) st.pop_back();          // top loses, keep fighting
                else { if (st.back() == -x) st.pop_back(); alive = false; }
            }
            if (alive) st.push_back(x);
        }
        cout << st.size() << '\n';
        for (size_t i = 0; i < st.size(); i++) cout << st[i] << " \n"[i + 1 == st.size()];
    }
}
