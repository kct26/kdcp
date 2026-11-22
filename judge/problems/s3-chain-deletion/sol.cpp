#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        vector<int> L(n), R(n), round_(n, -1);
        for (int i = 0; i < n; i++) L[i] = i - 1, R[i] = i + 1 < n ? i + 1 : -1;
        auto removable = [&](int i) {
            return round_[i] == -1 && L[i] != -1 && R[i] != -1 && a[i] == llabs(a[L[i]] - a[R[i]]);
        };
        vector<int> check(n);
        iota(check.begin(), check.end(), 0);
        for (int r = 1; ; r++) {
            vector<int> del;
            for (int i : check) if (removable(i)) { del.push_back(i); round_[i] = r; }
            if (del.empty()) break;
            vector<int> next;
            for (int i : del) {                // unlink; L/R of removed nodes stay valid for chaining
                if (L[i] != -1) R[L[i]] = R[i];
                if (R[i] != -1) L[R[i]] = L[i];
            }
            for (int i : del) {
                if (L[i] != -1 && round_[L[i]] == -1) next.push_back(L[i]);
                if (R[i] != -1 && round_[R[i]] == -1) next.push_back(R[i]);
            }
            sort(next.begin(), next.end());
            next.erase(unique(next.begin(), next.end()), next.end());
            check = next;
        }
        for (int i = 0; i < n; i++) cout << round_[i] << " \n"[i + 1 == n];
    }
}
