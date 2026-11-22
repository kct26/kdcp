#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        int rounds = 0;
        while (true) {
            vector<long long> b;
            for (size_t i = 0; i < a.size(); i++)
                if (!(i + 1 < a.size() && a[i] < a[i + 1])) b.push_back(a[i]);
            if (b.size() == a.size()) break;
            a = b; rounds++;
        }
        cout << rounds << '\n';
    }
}
