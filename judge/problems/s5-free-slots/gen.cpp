#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        int n = big ? 200000 : rnd(1, 6), q = big ? 200000 : rnd(1, 10);
        cout << n << ' ' << q << '\n';
        set<int> freeS; for (int i = 1; i <= n; i++) freeS.insert(i);
        vector<int> taken;                      // mirror of occupied spots for random releases
        for (int i = 0; i < q; i++) {
            if (!taken.empty() && rnd(0, 3) == 0) {
                int j = rnd(0, taken.size() - 1); int x = taken[j];
                swap(taken[j], taken.back()); taken.pop_back(); freeS.insert(x);
                cout << "2 " << x << '\n';
            } else {
                int l = rnd(1, n), r = rnd(l, n);
                if (big && rnd(0, 1)) l = 1, r = n;
                auto it = freeS.lower_bound(l);
                if (it != freeS.end() && *it <= r) { taken.push_back(*it); freeS.erase(it); }
                cout << "1 " << l << ' ' << r << '\n';
            }
        }
    }
}
