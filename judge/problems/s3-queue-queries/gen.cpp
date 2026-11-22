#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int q = big ? 200000 : rnd(1, 12);
        long long lim = big ? 1000000000 : 9;
        cout << q << '\n';
        for (int i = 0; i < q; i++) {
            int t = rnd(1, 3);
            if (t == 1) cout << "1 " << rnd(-lim, lim) << '\n';
            else cout << t << '\n';
        }
    }
}
