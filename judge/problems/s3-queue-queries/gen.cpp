#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
// Plain modulo and our own shuffle: their results are fixed by the seed alone, so the
// tests come out identical on every compiler and platform (the standard helpers do not).
long long rnd(long long l, long long r) { return l + (long long)(rng() % (unsigned long long)(r - l + 1)); }
template <class V> void shuf(V& v) { for (int i = (int)v.size() - 1; i > 0; i--) swap(v[i], v[rnd(0, i)]); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? (atoi(argv[1]) % 3 == 1 ? 10 : 3) : 30;   // the "long line" test packs 10 cases
    cout << T << '\n';
    while (T--) {
        int q = big ? 200000 : rnd(1, 12);
        long long lim = big ? 1000000000 : 9;
        cout << q << '\n';
        int shape = big ? atoi(argv[1]) % 3 : 0;
        for (int i = 0; i < q; i++) {
            int t = rnd(1, 3);
            if (shape == 1) t = i < q / 2 ? 1 : (i % 10 ? 2 : 3);       // a long line, then it empties
            if (shape == 2) t = i % 4 == 3 ? 2 : (i % 4 == 2 ? 3 : 1);  // grows steadily
            if (t == 1) cout << "1 " << (shape == 1 ? rnd(1, 9) : rnd(-lim, lim)) << '\n';
            else cout << t << '\n';
        }
    }
}
