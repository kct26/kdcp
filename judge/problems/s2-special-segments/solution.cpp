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
    stack<int> st;
    ll cnt = 0;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && st.top() < a[i]) {
            st.pop();
            cnt++;
        }
        if (!st.empty()) cnt++;
        st.push(a[i]);
    }
    cout << cnt << "\n";
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
