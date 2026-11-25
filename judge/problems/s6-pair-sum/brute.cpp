#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; long long M; cin >> n >> M;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        long long ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) ans += a[i] + a[j] == M;
        cout << ans << '\n';
    }
}
