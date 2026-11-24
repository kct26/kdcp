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
        long long budget = big ? 200000 : rnd(1, 12);
        vector<long long> a;
        int mode = rnd(0, 2);
        while (budget > 0) {
            long long x = mode == 0 ? 1 : mode == 1 ? rnd(1, min(budget, 7LL)) : rnd(1, budget);
            if (big && mode == 0) x = rnd(1, 2);
            x = min(x, budget);
            a.push_back(x); budget -= x;
        }
        cout << a.size() << '\n';
        for (size_t i = 0; i < a.size(); i++) cout << a[i] << " \n"[i + 1 == a.size()];
    }
}
