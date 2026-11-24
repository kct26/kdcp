// Correct (from the user): stack of (value, rounds needed to clear everything smaller before it).
#include <bits/stdc++.h>
using namespace std;
const int MAX = 200005;
int a[MAX], n;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    stack<pair<int,int>> st;
    int cnt = 0;
    for (int i = 0; i < n; i++){
        int tmp = 0;
        while (!st.empty() && st.top().first < a[i]){
            tmp = max(tmp + 1, st.top().second);
            st.pop();
        }
        st.push({a[i], tmp});
        cnt = max(cnt, tmp);
    }
    cout << cnt << "\n";
}

int main() { ios::sync_with_stdio(false); cin.tie(nullptr); int T; cin >> T; while (T--) solve(); }
