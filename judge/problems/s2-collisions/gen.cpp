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
        long long lim = big ? 1000000000 : 5;
        cout << n << '\n';
        for (int i = 0; i < n; i++) {
            long long v = rnd(1, lim);
            if (big && i >= n / 2) v = rnd(lim / 2, lim);      // big left-movers smash a long run
            cout << (big ? (i < n / 2 ? v : -v) : (rnd(0, 1) ? v : -v)) << " \n"[i + 1 == n];
        }
    }
}
