#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; long long K; cin >> n >> K;
        priority_queue<pair<long long,long long>> pq;   // (level - offset, splash)
        long long offset = 0;
        for (int i = 0; i < n; i++) {
            long long a, b, x; cin >> a >> b >> x;
            pq.push({a - offset, b});
            offset += x;
            int removed = 0;
            while (!pq.empty() && pq.top().first + offset >= K) {
                offset += pq.top().second; pq.pop(); removed++;
            }
            cout << removed << " \n"[i + 1 == n];
        }
    }
}
