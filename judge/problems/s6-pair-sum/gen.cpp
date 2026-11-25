#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
// Plain modulo and our own shuffle: their results are fixed by the seed alone, so the
// tests come out identical on every compiler and platform (the standard helpers do not).
long long rnd(long long l, long long r) { return l + (long long)(rng() % (unsigned long long)(r - l + 1)); }
template <class V> void shuf(V& v) { for (int i = (int)v.size() - 1; i > 0; i--) swap(v[i], v[rnd(0, i)]); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : 20;
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 10);
        const long long E = 1000000000000LL;
        vector<long long> a(n);
        long long M;
        int shape = big ? atoi(argv[1]) % 3 : rnd(0, 3);
        if (shape == 0) {                         // one repeated value: about n^2/2 pairs
            long long v = big ? rnd(-E, E) : rnd(-3, 3);
            for (auto& x : a) x = rnd(0, 9) ? v : rnd(-E, E);
            M = 2 * v;
        } else if (shape == 1) {                  // values from a small pool of huge numbers
            vector<long long> pool(big ? 1000 : 3);
            for (auto& p : pool) p = rnd(-E, E);
            for (auto& x : a) x = pool[rnd(0, pool.size() - 1)];
            M = pool[rnd(0, pool.size() - 1)] + pool[rnd(0, pool.size() - 1)];
        } else {
            long long lim = big ? E : 5;
            for (auto& x : a) x = rnd(-lim, lim);
            M = n >= 2 ? a[rnd(0, n - 1)] + a[rnd(0, n - 1)] : rnd(-2 * lim, 2 * lim);
        }
        cout << n << ' ' << M << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
    }
}
