#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

const int OFF = 2000000;
int cnt[2 * OFF + 1], a[MAX], b[MAX], freqOf[MAX], n, q, best;
vector<int> touched;

void add(int d) {
    int &c = cnt[d + OFF];
    if (c == 0) touched.push_back(d);
    freqOf[c]--;
    c++;
    freqOf[c]++;
    best = max(best, c);
}

void del(int d) {
    int &c = cnt[d + OFF];
    freqOf[c]--;
    if (c == best && freqOf[c] == 0) best--;
    c--;
    freqOf[c]++;
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int c = 0; c <= n + 1; c++) freqOf[c] = 0;
    best = 0;
    for (int i = 1; i <= n; i++) add(b[i] - a[i]);
    while (q--) {
        int t;
        cin >> t;
        if (t == 3) {
            cout << best << "\n";
            continue;
        }
        int i, x;
        cin >> i >> x;
        del(b[i] - a[i]);
        if (t == 1) a[i] = x;
        else b[i] = x;
        add(b[i] - a[i]);
    }
    for (int d : touched) cnt[d + OFF] = 0;
    touched.clear();
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
