#include <bits/stdc++.h>
using namespace std;

int n, k; vector<long long> b, d; long long best;
void go(int i, int left, long long sum) {          // decide how many uses machine i gets
    if (i == n) { if (left == 0) best = max(best, sum); return; }
    long long s = 0;
    for (int u = 0; u <= left; u++) {
        go(i + 1, left - u, sum + s);
        s += max(0LL, b[i] - u * d[i]);
    }
}
int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> k; b.assign(n, 0); d.assign(n, 0);
        for (int i = 0; i < n; i++) cin >> b[i] >> d[i];
        best = LLONG_MIN; go(0, k, 0);
        cout << best << '\n';
    }
}
