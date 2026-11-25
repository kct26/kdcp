#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; long long M; cin >> n >> M;
        map<long long, long long> cnt;          // value -> times seen so far
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long x; cin >> x;
            auto it = cnt.find(M - x);
            if (it != cnt.end()) ans += it->second;
            cnt[x]++;
        }
        cout << ans << '\n';
    }
}
