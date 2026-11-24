#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lb = long double;

const int MOD = 1000000007;
const int MAX = 200005;

pair<int,int> job[MAX];
int n;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> job[i].first >> job[i].second;
    sort(job, job + n);
    priority_queue<int, vector<int>, greater<int>> pq;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        pq.push(job[i].second);
        total += job[i].second;
        if ((int)pq.size() > job[i].first) {
            total -= pq.top();
            pq.pop();
        }
    }
    cout << total << "\n";
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
