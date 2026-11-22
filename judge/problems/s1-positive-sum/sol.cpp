#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        long long sum = 0;
        for (int i = 0; i < n; i++) { long long x; cin >> x; if (x > 0) sum += x; }
        cout << sum << '\n';
    }
}
