#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 9);
        set<long long> used; vector<long long> a;
        long long lim = big ? 1000000000 : 20;
        while ((int)a.size() < n) { long long v = rnd(1, lim); if (used.insert(v).second) a.push_back(v); }
        int shape = rnd(0, 2);                  // random, decreasing, or increasing
        if (shape == 1) sort(a.rbegin(), a.rend());
        if (shape == 2 && big) sort(a.begin(), a.end());
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
    }
}
