#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;
        vector<int> a(n + 1);
        map<int, set<int>> pos;                 // value -> positions holding it
        multiset<int> gaps;                     // distances between neighbouring equal values
        auto add = [&](int i, int v) {
            auto& s = pos[v];
            auto it = s.insert(i).first;
            int p = it != s.begin() ? *prev(it) : -1;
            int r = next(it) != s.end() ? *next(it) : -1;
            if (p != -1 && r != -1) gaps.erase(gaps.find(r - p));
            if (p != -1) gaps.insert(i - p);
            if (r != -1) gaps.insert(r - i);
        };
        auto remove = [&](int i, int v) {
            auto& s = pos[v];
            auto it = s.find(i);
            int p = it != s.begin() ? *prev(it) : -1;
            int r = next(it) != s.end() ? *next(it) : -1;
            if (p != -1) gaps.erase(gaps.find(i - p));
            if (r != -1) gaps.erase(gaps.find(r - i));
            if (p != -1 && r != -1) gaps.insert(r - p);
            s.erase(it);
        };
        for (int i = 1; i <= n; i++) { cin >> a[i]; add(i, a[i]); }
        while (q--) {
            int t; cin >> t;
            if (t == 1) {
                int i, x; cin >> i >> x;
                remove(i, a[i]);
                a[i] = x;
                add(i, x);
            } else {
                cout << (gaps.empty() ? -1 : *gaps.begin()) << '\n';
            }
        }
    }
}
