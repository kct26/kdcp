#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        bool changed = true;
        while (changed) {                       // resolve the leftmost collision each time
            changed = false;
            for (size_t i = 0; i + 1 < a.size(); i++) if (a[i] > 0 && a[i + 1] < 0) {
                long long p = a[i], q = -a[i + 1];
                if (p < q) a.erase(a.begin() + i);
                else if (p > q) a.erase(a.begin() + i + 1);
                else a.erase(a.begin() + i, a.begin() + i + 2);
                changed = true; break;
            }
        }
        cout << a.size() << '\n';
        for (size_t i = 0; i < a.size(); i++) cout << a[i] << " \n"[i + 1 == a.size()];
    }
}
