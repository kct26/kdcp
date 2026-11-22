#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 12);
        int bias = rnd(30, 70);                 // % chance of '('
        string s(n, '(');
        if (big && rnd(0, 1)) {                 // long balanced chunks with a few breaks
            for (int i = 0; i + 1 < n; i += 2) s[i] = '(', s[i + 1] = ')';
            for (int k = 0; k < 5; k++) s[rnd(0, n - 1)] = rnd(0, 1) ? '(' : ')';
        } else for (auto& c : s) c = rnd(1, 100) <= bias ? '(' : ')';
        cout << s << '\n';
    }
}
