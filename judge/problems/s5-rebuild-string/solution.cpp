#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int nxt[1000005];

int findNext(int i) {
    while (nxt[i] != i) {
        nxt[i] = nxt[nxt[i]];
        i = nxt[i];
    }
    return i;
}

void solve() {
    int n;
    cin >> n;
    vector<string> word(n);
    vector<vector<int>> pos(n);
    int len = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> word[i] >> k;
        pos[i].resize(k);
        for (int &x : pos[i]) {
            cin >> x;
            len = max(len, x + (int)word[i].size() - 1);
        }
    }
    for (int i = 0; i <= len + 1; i++) nxt[i] = i;
    string s(len + 1, '?');
    for (int i = 0; i < n; i++) {
        int m = word[i].size();
        for (int x : pos[i]) {
            for (int j = findNext(x); j < x + m; j = findNext(j)) {
                s[j] = word[i][j - x];
                nxt[j] = j + 1;
            }
        }
    }
    cout << s.substr(1) << "\n";
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
