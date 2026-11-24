// Wrong: sums the largest element of each segment instead of the second largest.
#include <bits/stdc++.h>
using namespace std;
int main() { ios::sync_with_stdio(false); cin.tie(nullptr); int T; cin >> T; while (T--) { int n; cin >> n;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    vector<int> L(n), R(n); stack<int> st;
    for (int i = 0; i < n; i++) { while (!st.empty() && a[st.top()] < a[i]) st.pop(); L[i] = st.empty() ? -1 : st.top(); st.push(i); }
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) { while (!st.empty() && a[st.top()] < a[i]) st.pop(); R[i] = st.empty() ? n : st.top(); st.push(i); }
    long long total = 0;
    for (int i = 0; i < n; i++) total += a[i] * ((long long)(i - L[i]) * (R[i] - i) - 1);
    cout << total << '\n'; } }
