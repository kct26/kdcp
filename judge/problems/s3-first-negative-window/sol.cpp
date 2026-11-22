#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        deque<int> neg;                         // positions of negatives, left to right
        vector<long long> out;
        for (int i = 0; i < n; i++) {
            if (a[i] < 0) neg.push_back(i);
            if (!neg.empty() && neg.front() <= i - k) neg.pop_front();
            if (i >= k - 1) out.push_back(neg.empty() ? 0 : a[neg.front()]);
        }
        for (size_t i = 0; i < out.size(); i++) cout << out[i] << " \n"[i + 1 == out.size()];
    }
}
