#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 8);
        long long cap = big ? 1000000000 : 6;
        long long K = big ? rnd(1, 1000000000000000LL) : rnd(1, 20);
        if (big && rnd(0, 1)) K = rnd(1000000000LL, 20000000000LL);
        cout << n << ' ' << K << '\n';
        for (int i = 0; i < n; i++)
            cout << rnd(0, cap) << ' ' << rnd(0, cap) << ' ' << rnd(0, big ? cap / 10 : cap) << '\n';
    }
}
