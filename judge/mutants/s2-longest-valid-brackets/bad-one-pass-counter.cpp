// Wrong: one left-to-right pass with open/close counters (misses "(()" style stretches).
#include <bits/stdc++.h>
using namespace std;
int main() { int T; cin >> T; while (T--) { string s; cin >> s; int open = 0, close = 0, best = 0;
    for (char c : s) { if (c == '(') open++; else close++;
        if (open == close) best = max(best, 2 * close); else if (close > open) open = close = 0; }
    cout << best << '\n'; } }
