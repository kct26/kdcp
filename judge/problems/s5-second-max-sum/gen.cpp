#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(2, 9);
        vector<int> p(n); iota(p.begin(), p.end(), 1);
        int shape = rnd(0, 2);
        if (shape == 0) shuffle(p.begin(), p.end(), rng);
        if (shape == 1) reverse(p.begin(), p.end());
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << p[i] << " \n"[i + 1 == n];
    }
}
