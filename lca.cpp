/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 4;
int n, root, a, b;
int par[N], high[N];
vector<int> adj[N];

void dfs1(int u) {
    for (int v : adj[u]) {
        if (v == par[u]) continue;
        par[v] = u;
        high[v] = high[u] + 1;
        dfs1(v);
    }
}

void setup(int root) {
    par[root] = root;
    high[root] = 0;
    dfs1(root);
    return;
}

int lca(int u, int v) {
    if (high[u] < high[v]) swap(v, u);
    while (high[u] > high[v]) u = par[u];
    if (u == v) return u;
    while (u != v) {
        u = par[u];
        v = par[v]; 
    }
    return u;
}

void sol() {
    cin >> n >> root;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> a >> b;
    setup(root);
    cout << lca(a, b);
    return;
} 

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("lca.inp", "r", stdin);
    freopen("lca.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}