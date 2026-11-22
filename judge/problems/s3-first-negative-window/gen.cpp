#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 9);
        int k = rnd(1, n);
        long long lim = big ? 1000000000 : 9;
        int negPct = rnd(0, 100);
        cout << n << ' ' << k << '\n';
        for (int i = 0; i < n; i++) {
            long long v = rnd(0, lim);
            if (rnd(1, 100) <= negPct && v > 0) v = -v;
            cout << v << " \n"[i + 1 == n];
        }
    }
}
