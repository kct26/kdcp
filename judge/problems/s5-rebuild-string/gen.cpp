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
        if (big && atoi(argv[1]) % 3 == 1) {                 // heavy overlap: one short word at almost every position
            int L = 1000000, m = 1000;
            cout << 1 << '\n' << string(m, 'a') << ' ' << (L - m + 1);
            for (int x = 1; x <= L - m + 1; x++) cout << ' ' << x;
            cout << '\n';
            continue;
        }
        int L = big ? 1000000 : rnd(1, 10);
        int alpha = big ? 26 : rnd(1, 3);
        string s; for (int i = 0; i < L; i++) s += char('a' + rnd(0, alpha - 1));
        vector<pair<string, vector<int>>> clues;
        vector<bool> covered(L + 1, false);
        int extra = big ? 0 : rnd(0, 3);
        auto addClue = [&](int p, int m) {      // word s[p..p+m), listed at every place it occurs
            string t = s.substr(p - 1, m);
            vector<int> at;
            if (big) at = {p};
            else for (int x = 1; x + m - 1 <= L; x++) if (s.compare(x - 1, m, t) == 0 && (x == p || rnd(0, 1))) at.push_back(x);
            for (int x : at) for (int j = x; j < x + m; j++) covered[j] = true;
            clues.push_back({t, at});
        };
        for (int e = 0; e < extra; e++) { int p = rnd(1, L); addClue(p, rnd(1, L - p + 1)); }
        for (int p = 1; p <= L; ) {             // make sure every position is covered
            if (covered[p]) { p++; continue; }
            int m = big ? rnd(1, 1000) : rnd(1, 3); m = min(m, L - p + 1);
            addClue(p, m); p += m;
        }
        shuf(clues);
        cout << clues.size() << '\n';
        for (auto& [t, at] : clues) {
            cout << t << ' ' << at.size();
            for (int x : at) cout << ' ' << x;
            cout << '\n';
        }
    }
}
