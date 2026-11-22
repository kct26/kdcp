#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        long long n; int q; cin >> n >> q;
        set<long long> marks = {0, n};
        multiset<long long> gaps = {n};
        while (q--) {
            int t; long long x; cin >> t >> x;
            if (t == 1) {
                auto it = marks.insert(x).first;
                long long l = *prev(it), r = *next(it);
                gaps.erase(gaps.find(r - l));
                gaps.insert(x - l); gaps.insert(r - x);
            } else {
                auto it = marks.find(x);
                long long l = *prev(it), r = *next(it);
                gaps.erase(gaps.find(x - l)); gaps.erase(gaps.find(r - x));
                gaps.insert(r - l);
                marks.erase(it);
            }
            cout << *gaps.rbegin() << '\n';
        }
    }
}
