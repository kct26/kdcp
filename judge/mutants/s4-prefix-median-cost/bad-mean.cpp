// Wrong: meets at the (rounded) average instead of a median.
#include <bits/stdc++.h>
using namespace std;
int main() { ios::sync_with_stdio(false); cin.tie(nullptr); int T; cin >> T; while (T--) { int n; cin >> n;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    long long sum = 0;
    for (int i = 0; i < n; i++) { sum += a[i]; long long m = llround((double)sum / (i + 1)), c = 0;
        for (int j = 0; j <= i && j < 3000; j++) c += llabs(a[j] - m);
        cout << c << " \n"[i + 1 == n]; } } }
