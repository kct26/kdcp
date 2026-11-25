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
        int shape = big ? atoi(argv[1]) % 3 : rnd(0, 2);
        if (shape == 0) {                         // many repeats of huge values
            vector<long long> pool(big ? 1000 : 3);
            for (auto& p : pool) p = rnd(-E, E);
            for (auto& x : a) x = pool[rnd(0, pool.size() - 1)];
        } else if (shape == 1) {
            for (auto& x : a) x = rnd(-E, E);
        } else {
            for (auto& x : a) x = big ? rnd(-1000, 1000) : rnd(-3, 3);
            sort(a.rbegin(), a.rend());
        }
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
    }
}
