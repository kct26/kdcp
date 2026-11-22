#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; long long K; cin >> n >> K;
        vector<long long> lvl, sp;
        for (int i = 0; i < n; i++) {
            long long a, b, x; cin >> a >> b >> x;
            lvl.push_back(a); sp.push_back(b);
            for (auto& v : lvl) v += x;
            int removed = 0;
            while (true) {
                int j = -1;
                for (int t = 0; t < (int)lvl.size(); t++) if (lvl[t] >= K) { j = t; break; }  // leftmost, not highest
                if (j < 0) break;
                long long s = sp[j];
                lvl.erase(lvl.begin() + j); sp.erase(sp.begin() + j);
                for (auto& v : lvl) v += s;
                removed++;
            }
            cout << removed << " \n"[i + 1 == n];
        }
    }
}
