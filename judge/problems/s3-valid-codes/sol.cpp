#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const int K = 200000;
    vector<string> codes;                       // BFS order = length, then dictionary order
    queue<string> q;
    for (string s : {"1", "2", "3"}) q.push(s);
    while ((int)codes.size() < K) {
        string s = q.front(); q.pop();
        codes.push_back(s);
        for (char c = '1'; c <= '3'; c++) if (c != s.back()) q.push(s + c);
    }
    int T; cin >> T;
    while (T--) { int k; cin >> k; cout << codes[k - 1] << '\n'; }
}
