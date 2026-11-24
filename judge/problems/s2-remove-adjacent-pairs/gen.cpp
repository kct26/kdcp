#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
// Plain modulo and our own shuffle: their results are fixed by the seed alone, so the
// tests come out identical on every compiler and platform (the standard helpers do not).
long long rnd(long long l, long long r) { return l + (long long)(rng() % (unsigned long long)(r - l + 1)); }
template <class V> void shuf(V& v) { for (int i = (int)v.size() - 1; i > 0; i--) swap(v[i], v[rnd(0, i)]); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 5 : 30;
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 12);
        int alpha = big ? rnd(2, 26) : rnd(1, 3);
        string s;
        if (big && atoi(argv[1]) % 3 != 2) {                 // a palindrome of even length cancels completely
            string h; for (int i = 0; i < n / 2; i++) h += char('a' + rnd(0, alpha - 1));
            s = h + string(h.rbegin(), h.rend());
        } else for (int i = 0; i < n; i++) s += char('a' + rnd(0, alpha - 1));
        cout << s << '\n';
    }
}
