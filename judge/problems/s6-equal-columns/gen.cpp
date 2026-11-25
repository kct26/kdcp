#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
// Plain modulo and our own shuffle: their results are fixed by the seed alone, so the
// tests come out identical on every compiler and platform (the standard helpers do not).
long long rnd(long long l, long long r) { return l + (long long)(rng() % (unsigned long long)(r - l + 1)); }
template <class V> void shuf(V& v) { for (int i = (int)v.size() - 1; i > 0; i--) swap(v[i], v[rnd(0, i)]); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 4 : 20;
    cout << T << '\n';
    while (T--) {
        int shape = big ? atoi(argv[1]) % 3 : rnd(0, 2);
        int n = big ? 50000 : rnd(1, 8);
        int m = big ? (shape == 1 ? 3 : 10) : rnd(1, 4);
        cout << n << ' ' << m << '\n';
        for (int i = 0; i < n; i++) {
            vector<int> row(m, 0);
            if (shape == 0) for (auto& x : row) x = rnd(0, 1);
            if (shape == 1) row[rnd(0, m - 1)] = 1;                  // one 1 per row
            if (shape == 2) { int v = rnd(0, 1); for (auto& x : row) x = v; if (!rnd(0, 20)) row[rnd(0, m - 1)] ^= 1; }
            for (int j = 0; j < m; j++) cout << row[j] << " \n"[j + 1 == m];
        }
    }
}
