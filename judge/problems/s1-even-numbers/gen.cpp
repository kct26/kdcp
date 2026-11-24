#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
// Plain modulo and our own shuffle: their results are fixed by the seed alone, so the
// tests come out identical on every compiler and platform (the standard helpers do not).
long long rnd(long long l, long long r) { return l + (long long)(rng() % (unsigned long long)(r - l + 1)); }
template <class V> void shuf(V& v) { for (int i = (int)v.size() - 1; i > 0; i--) swap(v[i], v[rnd(0, i)]); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : 30;
    cout << T << '\n';
    while (T--) {
        int n = big ? 100000 : rnd(1, 8);
        long long lim = big ? 1000000000 : 10;
        bool allOdd = !big && rnd(0, 3) == 0;
        cout << n << '\n';
        for (int i = 0; i < n; i++) {
            long long x = rnd(-lim, lim);
            if (allOdd && x % 2 == 0) x += (x < lim ? 1 : -1);
            cout << x << " \n"[i + 1 == n];
        }
    }
}
