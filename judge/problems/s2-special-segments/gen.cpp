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
        int n = big ? 200000 : rnd(1, 9);
        set<long long> used; vector<long long> a;
        long long lim = big ? 1000000000 : 20;
        while ((int)a.size() < n) { long long v = rnd(1, lim); if (used.insert(v).second) a.push_back(v); }
        int shape = big ? atoi(argv[1]) % 3 : rnd(0, 2);                  // random, decreasing, or increasing
        if (shape == 1) sort(a.rbegin(), a.rend());
        if (shape == 2 && big) sort(a.begin(), a.end());
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
    }
}
