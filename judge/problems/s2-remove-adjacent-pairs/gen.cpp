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
        int alpha = big ? rnd(2, 26) : rnd(1, 3);
        string s;
        if (big && rnd(0, 1)) {                 // a palindrome of even length cancels completely
            string h; for (int i = 0; i < n / 2; i++) h += char('a' + rnd(0, alpha - 1));
            s = h + string(h.rbegin(), h.rend());
        } else for (int i = 0; i < n; i++) s += char('a' + rnd(0, alpha - 1));
        cout << s << '\n';
    }
}
