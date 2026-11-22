#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 6), q = big ? 200000 : rnd(1, 10);
        long long lim = big ? 1000000000 : 4;
        int k = rnd(0, n);
        vector<long long> a(n); for (auto& x : a) x = rnd(-lim, lim);
        cout << n << ' ' << q << ' ' << k << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
        for (int i = 0; i < q; i++) {
            if (rnd(0, 1)) {
                int j = rnd(0, n - 1); long long y = rnd(-lim, lim);
                cout << "1 " << a[j] << ' ' << y << '\n'; a[j] = y;
            } else {
                int nk = k + (int)rnd(-1, 1); nk = max(0, min(n, nk)); k = nk;
                cout << "2 " << k << '\n';
            }
        }
    }
}
