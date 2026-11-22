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
        long long dmax = big ? (rnd(0, 1) ? n : 50) : rnd(1, n);
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << rnd(1, dmax) << ' ' << rnd(1, big ? 1000000000 : 20) << '\n';
    }
}
