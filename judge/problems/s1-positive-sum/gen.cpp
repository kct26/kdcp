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
        long long lo = big ? (atoi(argv[1]) % 3 != 0 ? 1000000 : -1000000) : -5;
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << (big && lo > 0 ? 1000000 - rnd(0, 3) : rnd(-1000000 * big - 5 * !big, 1000000 * big + 5 * !big)) << " \n"[i + 1 == n];
    }
}
