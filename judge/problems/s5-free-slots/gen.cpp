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
        int n = big ? 200000 : rnd(1, 6), q = big ? 200000 : rnd(1, 10);
        cout << n << ' ' << q << '\n';
        set<int> freeS; for (int i = 1; i <= n; i++) freeS.insert(i);
        vector<int> taken;                      // mirror of occupied spots for random releases
        int shape = big ? atoi(argv[1]) % 3 : 0;
        for (int i = 0; i < q; i++) {
            bool fillFromStart = shape == 1 && i < q * 3 / 4;          // the street fills up from spot 1
            if (!fillFromStart && !taken.empty() && rnd(0, 3) == 0) {
                int j = rnd(0, taken.size() - 1); int x = taken[j];
                swap(taken[j], taken.back()); taken.pop_back(); freeS.insert(x);
                cout << "2 " << x << '\n';
            } else {
                int l = rnd(1, n), r = rnd(l, n);
                if ((big && rnd(0, 1)) || fillFromStart) l = 1, r = n;
                if (shape == 2) r = n;
                auto it = freeS.lower_bound(l);
                if (it != freeS.end() && *it <= r) { taken.push_back(*it); freeS.erase(it); }
                cout << "1 " << l << ' ' << r << '\n';
            }
        }
    }
}
