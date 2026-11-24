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
        int n = big ? 200000 : rnd(3, 10);
        long long lim = big ? 3 : rnd(1, 4);
        vector<long long> a(n);
        for (auto& x : a) x = rnd(0, lim);
        int shape = big ? atoi(argv[1]) % 3 : rnd(0, 5);
        long long A = big ? rnd(1, 1000000000) : rnd(1, 4);
        // "A A ... A 0" loses one element per round from the right; "0 A ... A 0" from both ends
        if (shape == 1) { for (auto& x : a) x = A; a[n - 1] = 0; }
        if (shape == 2) { for (auto& x : a) x = A; a[0] = a[n - 1] = 0; }
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
    }
}
