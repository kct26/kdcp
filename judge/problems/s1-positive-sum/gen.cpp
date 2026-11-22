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
        long long lo = big ? (rnd(0, 1) ? 1000000 : -1000000) : -5;
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << (big && lo > 0 ? 1000000 - rnd(0, 3) : rnd(-1000000 * big - 5 * !big, 1000000 * big + 5 * !big)) << " \n"[i + 1 == n];
    }
}
