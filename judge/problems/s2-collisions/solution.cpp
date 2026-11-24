#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

int a[MAX], n;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> st;
    for (int i = 0; i < n; i++) {
        bool alive = true;
        while (alive && a[i] < 0 && !st.empty() && st.back() > 0) {
            if (st.back() < -a[i]) st.pop_back();
            else {
                if (st.back() == -a[i]) st.pop_back();
                alive = false;
            }
        }
        if (alive) st.push_back(a[i]);
    }
    cout << st.size() << "\n";
    for (int i = 0; i < (int)st.size(); i++) cout << st[i] << " \n"[i + 1 == (int)st.size()];
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
