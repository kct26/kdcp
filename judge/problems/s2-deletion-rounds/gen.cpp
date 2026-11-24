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
        int n = big ? 200000 : rnd(1, 12);
        long long lim = big ? 1000000000 : rnd(1, 6);
        vector<long long> a(n);
        for (auto& x : a) x = rnd(1, lim);
        if (big) {
            int shape = atoi(argv[1]) % 3;
            if (shape == 0) for (auto& x : a) x = rnd(1, 5);              // many equal values, long chains
            if (shape == 1) { sort(a.begin(), a.end()); }                 // increasing: 1 round
            if (shape == 2) { for (int i = 0; i < n; i++) a[i] = (i == n - 1) ? lim : n - i; } // many rounds
        }
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
    }
}
