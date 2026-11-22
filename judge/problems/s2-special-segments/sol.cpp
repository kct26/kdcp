#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> st;                   // decreasing heights
        long long pairs = 0;
        for (int i = 0; i < n; i++) {
            long long x; cin >> x;
            while (!st.empty() && st.back() < x) { st.pop_back(); pairs++; }
            if (!st.empty()) pairs++;           // the first taller tower to the left
            st.push_back(x);
        }
        cout << pairs << '\n';
    }
}
