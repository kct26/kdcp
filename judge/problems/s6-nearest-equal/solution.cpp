#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int a[MAX], n, q;
map<int, set<int>> pos;
multiset<int> gaps;

void add(int i, int v) {
    set<int>& s = pos[v];
    auto it = s.insert(i).first;
    int p = (it != s.begin()) ? *prev(it) : -1;
    int r = (next(it) != s.end()) ? *next(it) : -1;
    if (p != -1 && r != -1) gaps.erase(gaps.find(r - p));
    if (p != -1) gaps.insert(i - p);
    if (r != -1) gaps.insert(r - i);
}

void removePos(int i, int v) {
    set<int>& s = pos[v];
    auto it = s.find(i);
    int p = (it != s.begin()) ? *prev(it) : -1;
    int r = (next(it) != s.end()) ? *next(it) : -1;
    if (p != -1) gaps.erase(gaps.find(i - p));
    if (r != -1) gaps.erase(gaps.find(r - i));
    if (p != -1 && r != -1) gaps.insert(r - p);
    s.erase(it);
}

void solve() {
    cin >> n >> q;
    pos.clear();
    gaps.clear();
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        add(i, a[i]);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            removePos(i, a[i]);
            a[i] = x;
            add(i, x);
        } else {
            if (gaps.empty()) cout << -1 << "\n";
            else cout << *gaps.begin() << "\n";
        }
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
