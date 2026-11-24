#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int n, q;

void solve() {
    cin >> n >> q;
    set<int> marks = {0, n};
    multiset<int> gaps = {n};
    while (q--) {
        int t, x;
        cin >> t >> x;
        if (t == 1) {
            auto it = marks.insert(x).first;
            int l = *prev(it), r = *next(it);
            gaps.erase(gaps.find(r - l));
            gaps.insert(x - l);
            gaps.insert(r - x);
        } else {
            auto it = marks.find(x);
            int l = *prev(it), r = *next(it);
            gaps.erase(gaps.find(x - l));
            gaps.erase(gaps.find(r - x));
            gaps.insert(r - l);
            marks.erase(it);
        }
        cout << *gaps.rbegin() << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    int test = 1;
    cin >> test;
    while (test--) {
        solve();
    }
    return 0;
}
