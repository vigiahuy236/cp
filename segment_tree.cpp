/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 6;
const long long inf = (1LL<<62);

struct segtree {
    vector<long long> st, lazy;
    segtree(int n = 0) {
        init(n);
    } 
    void init(int n) {
        st.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }
    void push(int id) {
        if (lazy[id] != 0) {
            st[2 * id] += lazy[id];
            st[2 * id + 1] += lazy[id];
            lazy[2 * id] += lazy[id];
            lazy[2 * id + 1] += lazy[id];
            lazy[id] = 0;
        }
        return;
    }
    void build(int id, int l, int r, long long a[]) {
        if (l == r) {
            st[id] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * id, l, mid, a);
        build(2 * id + 1, mid + 1, r, a);
        st[id] = max(st[2 * id], st[2 * id + 1]);
    }
    void update(int id, int l, int r, int u, int v, long long k) {
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            st[id] += k;
            lazy[id] += k;
            return;
        }
        push(id);
        int mid = (l + r) / 2;
        update(2 * id, l, mid, u, v, k);
        update(2 * id + 1, mid + 1, r, u, v, k);
        st[id] = max(st[2 * id], st[2 * id + 1]);
    }
    long long get(int id, int l, int r, int u, int v) {
        if (v < l || r < u) return -inf;
        if (u <= l && r <= v) return st[id];
        push(id);
        int mid = (l + r) / 2;
        return max(get(2 * id, l, mid, u, v), get(2 * id + 1, mid + 1, r, u, v));
    }
};

void sol() {
    int n, q; cin >> n >> q;
    long long a[N];
    for (int i = 1; i <= n; i++) cin >> a[i];
    segtree seg(n);
    seg.build(1, 1, n, a);
    while (q--) {
        char type; cin >> type;
        if (type == '?') {
            int l, r; cin >> l >> r;
            cout << seg.get(1, 1, n, l, r) << "\n";
        } else {
            int l, r; cin >> l >> r;
            long long k; cin >> k;
            seg.update(1, 1, n, l, r, k);
        } 
    }
    return;
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("segment_tree.inp", "r", stdin);
    // freopen("segment_tree.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}