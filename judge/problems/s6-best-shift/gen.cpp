#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
// Plain modulo and our own shuffle: their results are fixed by the seed alone, so the
// tests come out identical on every compiler and platform (the standard helpers do not).
long long rnd(long long l, long long r) { return l + (long long)(rng() % (unsigned long long)(r - l + 1)); }
template <class V> void shuf(V& v) { for (int i = (int)v.size() - 1; i > 0; i--) swap(v[i], v[rnd(0, i)]); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : 10;
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 6), q = big ? 200000 : rnd(1, 12);
        int shape = big ? atoi(argv[1]) % 3 : rnd(0, 2);
        long long lim = shape == 0 ? 1000000 : (big ? 10 : 2);
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++) {
            a[i] = rnd(-lim, lim);
            b[i] = shape == 2 ? a[i] + 1 : rnd(-lim, lim);    // shape 2: every difference equal at first
        }
        cout << n << ' ' << q << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
        for (int i = 0; i < n; i++) cout << b[i] << " \n"[i + 1 == n];
        for (int k = 0; k < q; k++) {
            int t = rnd(1, 3);
            if (t == 3 || (big && k % 2)) cout << "3\n";
            else cout << t << ' ' << rnd(1, n) << ' ' << rnd(-lim, lim) << '\n';
        }
    }
}
