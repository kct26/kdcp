#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        const long long NONE = LLONG_MIN;
        long long best = NONE, second = NONE;
        for (int i = 0; i < n; i++) {
            long long x; cin >> x;
            if (x > best) { second = best; best = x; }
            else if (x < best && x > second) second = x;
        }
        cout << (second == NONE ? -1 : second) << '\n';
    }
}
