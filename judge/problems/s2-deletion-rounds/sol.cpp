#include <bits/stdc++.h>
using namespace std;

// die[i] = round in which a[i] is removed (0 = never). Scan right to left:
// a[i] survives forever if nothing to its right is larger; otherwise it dies one round
// after the slowest-dying element between it and the first larger element on its right.
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        vector<pair<long long,int>> st;         // (value, death round) of elements to the right
        int answer = 0;
        for (int i = n - 1; i >= 0; i--) {
            int slowest = 0;
            while (!st.empty() && st.back().first <= a[i]) {
                slowest = max(slowest, st.back().second);
                st.pop_back();
            }
            int die = st.empty() ? 0 : slowest + 1;
            answer = max(answer, die);
            st.push_back({a[i], die});
        }
        cout << answer << '\n';
    }
}
