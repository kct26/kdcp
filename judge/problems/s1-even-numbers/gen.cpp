#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int n = big ? 100000 : rnd(1, 8);
        long long lim = big ? 1000000000 : 10;
        bool allOdd = !big && rnd(0, 3) == 0;
        cout << n << '\n';
        for (int i = 0; i < n; i++) {
            long long x = rnd(-lim, lim);
            if (allOdd && x % 2 == 0) x += (x < lim ? 1 : -1);
            cout << x << " \n"[i + 1 == n];
        }
    }
}
