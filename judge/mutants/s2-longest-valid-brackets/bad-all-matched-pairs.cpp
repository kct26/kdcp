// Wrong: counts every matched pair in the whole string, contiguous or not.
#include <bits/stdc++.h>
using namespace std;
int main() { int T; cin >> T; while (T--) { string s; cin >> s; int open = 0, pairs = 0;
    for (char c : s) { if (c == '(') open++; else if (open) open--, pairs++; }
    cout << 2 * pairs << '\n'; } }
