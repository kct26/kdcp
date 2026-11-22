#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, q; long long k; cin >> n >> q >> k;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        sort(a.rbegin(), a.rend());
        multiset<long long> top, rest;
        long long sum = 0;
        for (int i = 0; i < n; i++) (i < k ? (sum += a[i], top) : rest).insert(a[i]);

        auto rebalance = [&]() {
            while ((long long)top.size() > k) { auto it = top.begin(); sum -= *it; rest.insert(*it); top.erase(it); }
            while ((long long)top.size() < k) { auto it = prev(rest.end()); sum += *it; top.insert(*it); rest.erase(it); }
            while (!top.empty() && !rest.empty() && *prev(rest.end()) > *top.begin()) {
                auto lo = top.begin(), hi = prev(rest.end());
                long long u = *lo, v = *hi;
                top.erase(lo); rest.erase(hi);
                top.insert(v); rest.insert(u); sum += v - u;
            }
        };
        while (q--) {
            int t; cin >> t;
            if (t == 1) {
                long long x, y; cin >> x >> y;
                auto it = rest.find(x);
                if (it != rest.end()) rest.erase(it);
                else { it = top.find(x); sum -= x; top.erase(it); }
                rest.insert(y);
            } else cin >> k;
            rebalance();
            cout << sum << '\n';
        }
    }
}
