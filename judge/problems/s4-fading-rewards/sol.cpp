#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        priority_queue<pair<long long,long long>> pq;   // (current payout, decrease)
        for (int i = 0; i < n; i++) { long long b, d; cin >> b >> d; pq.push({b, d}); }
        long long total = 0;
        while (k--) {
            auto [v, d] = pq.top(); pq.pop();
            total += v;
            pq.push({max(0LL, v - d), d});
        }
        cout << total << '\n';
    }
}
