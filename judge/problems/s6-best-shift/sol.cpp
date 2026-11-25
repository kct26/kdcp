#include <bits/stdc++.h>
using namespace std;

const int OFF = 2000000;                        // differences lie in [-2e6, 2e6]
int cntOf[2 * OFF + 1];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;
        vector<int> a(n + 1), b(n + 1), freq(n + 2, 0);   // freq[c] = differences seen exactly c times
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        int best = 0;
        vector<int> touched;
        auto inc = [&](int d) {
            int& c = cntOf[d + OFF];
            if (c == 0) touched.push_back(d);
            freq[c]--; c++; freq[c]++;
            best = max(best, c);
        };
        auto dec = [&](int d) {
            int& c = cntOf[d + OFF];
            freq[c]--;
            if (c == best && freq[c] == 0) best--;
            c--; freq[c]++;
        };
        for (int i = 1; i <= n; i++) inc(b[i] - a[i]);
        while (q--) {
            int t; cin >> t;
            if (t == 3) { cout << best << '\n'; continue; }
            int i, x; cin >> i >> x;
            dec(b[i] - a[i]);
            if (t == 1) a[i] = x; else b[i] = x;
            inc(b[i] - a[i]);
        }
        for (int d : touched) cntOf[d + OFF] = 0;
    }
}
