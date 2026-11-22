#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> where(n + 1);
        for (int i = 1; i <= n; i++) { int v; cin >> v; where[v] = i; }
        // positions of larger values, with two sentinels on each side
        set<int> big = {-1, 0, n + 1, n + 2};
        long long total = 0;
        for (int v = n; v >= 1; v--) {
            int i = where[v];
            auto it = big.insert(i).first;
            int l1 = *prev(it), l2 = *prev(prev(it));        // nearest / second-nearest larger on the left
            int r1 = *next(it), r2 = *next(next(it));        // same on the right
            if (l2 < 0) l2 = 0;                              // clamp sentinels to the array ends
            if (r2 > n + 1) r2 = n + 1;
            long long cnt = 0;
            if (l1 >= 1) cnt += (long long)(l1 - l2) * (r1 - i);   // exactly one larger element: on the left
            if (r1 <= n) cnt += (long long)(r2 - r1) * (i - l1);   // or on the right
            total += cnt * v;
        }
        cout << total << '\n';
    }
}
