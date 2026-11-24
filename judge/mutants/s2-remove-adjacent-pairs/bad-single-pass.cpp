// Wrong: removes neighbouring equal pairs in one pass, without the follow-up removals.
#include <bits/stdc++.h>
using namespace std;
int main() { int T; cin >> T; while (T--) { string s, out; cin >> s;
    for (size_t i = 0; i < s.size(); i++) { if (i + 1 < s.size() && s[i] == s[i + 1]) i++; else out += s[i]; }
    cout << (out.empty() ? "-" : out) << '\n'; } }
