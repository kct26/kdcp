#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        priority_queue<long long> lo;                              // max-heap, holds the median on top
        priority_queue<long long, vector<long long>, greater<>> hi;
        long long sumLo = 0, sumHi = 0;
        for (int i = 0; i < n; i++) {
            long long x; cin >> x;
            if (lo.empty() || x <= lo.top()) lo.push(x), sumLo += x;
            else hi.push(x), sumHi += x;
            if (lo.size() > hi.size() + 1) { long long v = lo.top(); lo.pop(); sumLo -= v; hi.push(v); sumHi += v; }
            if (hi.size() > lo.size())     { long long v = hi.top(); hi.pop(); sumHi -= v; lo.push(v); sumLo += v; }
            long long m = lo.top();
            long long cost = (m * (long long)lo.size() - sumLo) + (sumHi - m * (long long)hi.size());
            cout << cost << " \n"[i + 1 == n];
        }
    }
}
