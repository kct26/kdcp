#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 10);
        long long lim = big ? 1000000000 : rnd(1, 6);
        vector<long long> a(n);
        for (auto& x : a) x = rnd(1, lim);
        if (big) {
            int shape = rnd(0, 2);
            if (shape == 1) { sort(a.begin(), a.end()); }                 // increasing: 1 round
            if (shape == 2) { for (int i = 0; i < n; i++) a[i] = (i == n - 1) ? lim : n - i; } // many rounds
        }
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
    }
}
