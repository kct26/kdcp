#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
long long rnd(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rng); }
int main(int argc, char** argv) {
    rng.seed(atoll(argv[1])); bool big = string(argv[2]) == "large";
    int T = big ? 1 : rnd(1, 5);
    cout << T << '\n';
    while (T--) {
        long long n = big ? (rnd(0, 1) ? 1000000000 : 300000) : rnd(2, 10);
        int q = big ? 200000 : rnd(1, 10);
        cout << n << ' ' << q << '\n';
        set<long long> painted; vector<long long> list;    // list mirrors painted for random picks
        for (int i = 0; i < q; i++) {
            bool canPaint = (long long)painted.size() < n - 1;
            bool erase = !painted.empty() && (!canPaint || rnd(0, 2) == 0);
            if (erase) {
                int j = rnd(0, list.size() - 1);
                long long x = list[j]; swap(list[j], list.back()); list.pop_back(); painted.erase(x);
                cout << "2 " << x << '\n';
            } else {
                long long x;
                do x = rnd(1, n - 1); while (painted.count(x));
                painted.insert(x); list.push_back(x);
                cout << "1 " << x << '\n';
            }
        }
    }
}
