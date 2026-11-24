// Wrong (reported by the user): takes the most pops in a single step,
// which misses chains where an element dies only after its neighbours are gone.
#include <bits/stdc++.h>
using namespace std;
const int MAX = 200005;
int a[MAX], n;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    stack<int> st;
    int cnt = 0;
    for (int i = 0; i < n; i++){
        int tmp = 0;
        while (!st.empty() && st.top() < a[i]){
            st.pop();
            tmp++;
        }
        st.push(a[i]);
        cnt = max(cnt, tmp);
    }
    cout << cnt << "\n";
}

int main() { ios::sync_with_stdio(false); cin.tie(nullptr); int T; cin >> T; while (T--) solve(); }
