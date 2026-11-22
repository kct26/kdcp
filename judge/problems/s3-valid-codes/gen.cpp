#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 30 : rnd(1, 5);
    cout << T << '\n';
    while (T--) cout << (big ? rnd(1, 200000) : rnd(1, 2000)) << '\n';
}
