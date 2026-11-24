#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

vector<string> codes;

void build() {
    queue<string> q;
    q.push("1"); q.push("2"); q.push("3");
    while ((int)codes.size() < MAX) {
        string s = q.front();
        q.pop();
        codes.push_back(s);
        for (char c = '1'; c <= '3'; c++) {
            if (c != s.back()) q.push(s + c);
        }
    }
}

void solve() {
    if (codes.empty()) build();
    int k;
    cin >> k;
    cout << codes[k - 1] << "\n";
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
