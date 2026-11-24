#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

ll a[MAX];
int L[MAX], R[MAX], res[MAX], n;

bool canDelete(int i) {
    return res[i] == -1 && L[i] != -1 && R[i] != -1 && a[i] == llabs(a[L[i]] - a[R[i]]);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        L[i] = i - 1;
        R[i] = (i + 1 < n) ? i + 1 : -1;
        res[i] = -1;
    }
    vector<int> check(n);
    iota(check.begin(), check.end(), 0);
    for (int round = 1; ; round++) {
        vector<int> del;
        for (int i : check) {
            if (canDelete(i)) {
                del.push_back(i);
                res[i] = round;
            }
        }
        if (del.empty()) break;
        for (int i : del) {
            if (L[i] != -1) R[L[i]] = R[i];
            if (R[i] != -1) L[R[i]] = L[i];
        }
        vector<int> nxt;
        for (int i : del) {
            if (L[i] != -1 && res[L[i]] == -1) nxt.push_back(L[i]);
            if (R[i] != -1 && res[R[i]] == -1) nxt.push_back(R[i]);
        }
        sort(nxt.begin(), nxt.end());
        nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
        check = nxt;
    }
    for (int i = 0; i < n; i++) cout << res[i] << " \n"[i + 1 == n];
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
