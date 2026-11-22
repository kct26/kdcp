#include <bits/stdc++.h>
using namespace std;

vector<int> nxt;                                 // nxt[i] = first unfilled position >= i (path-compressed)
int findNext(int i) {
    while (nxt[i] != i) { nxt[i] = nxt[nxt[i]]; i = nxt[i]; }
    return i;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<string> words(n);
        vector<vector<int>> pos(n);
        int len = 0;
        for (int i = 0; i < n; i++) {
            int k; cin >> words[i] >> k;
            pos[i].resize(k);
            for (auto& x : pos[i]) { cin >> x; len = max(len, x + (int)words[i].size() - 1); }
        }
        string s(len + 1, '?');                  // 1-indexed
        nxt.resize(len + 2);
        iota(nxt.begin(), nxt.end(), 0);
        for (int i = 0; i < n; i++) {
            int m = words[i].size();
            for (int x : pos[i])
                for (int j = findNext(x); j < x + m; j = findNext(j)) {
                    s[j] = words[i][j - x];
                    nxt[j] = j + 1;
                }
        }
        cout << s.substr(1) << '\n';
    }
}
