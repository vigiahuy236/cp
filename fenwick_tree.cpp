/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 6;

struct fenwick {
    int n;
    vector<long long> bit;
    fenwick(int _n = 0) {
        init(_n);
    }
    void init(int _n) {
        n = _n;
        bit.assign(n + 1, 0);
    }
    void build(long long a[]) {
        for (int i = 1; i <= n; i++) {
            bit[i] += a[i];
            int j = i + (i & -i);
            if (j <= n) bit[j] += bit[i];
        }
    }
    long long get(int idx) {
        long long res = 0;
        while (idx > 0) {
            res += bit[idx];
            idx -= (idx & (-idx));
        }
        return res;
    }
    long long get_range(int l, int r) {
        return get(r) - get(l - 1);
    }
    void update(int idx, long long k) {
        while (idx <= n) {
            bit[idx] += k;
            idx += (idx & (-idx));
        }
    }
};

void sol() {
    int n, q; cin >> n >> q;
    long long a[N];
    for (int i = 1; i <= n; i++) cin >> a[i];
    fenwick fw(n);
    fw.build(a);
    while (q--) {
        char type; cin >> type;
        if (type == '?') {
            int l, r; cin >> l >> r;
            cout << fw.get_range(l, r) << "\n";
        } else {
            int p; cin >> p;
            long long k; cin >> k;
            fw.update(p, k);
        }
    }
    return;
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("fenwick_tree.inp", "r", stdin);
    // freopen("fenwick_tree.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}