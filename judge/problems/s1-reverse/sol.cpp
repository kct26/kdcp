#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        for (int i = n - 1; i >= 0; i--) cout << a[i] << " \n"[i == 0];
    }
}
