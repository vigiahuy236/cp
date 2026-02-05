/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 6;
int n, m, _n, timer;
int num[N], low[N], d[N];
vector<int> adj[N], comp[N], g[N];
stack<int> stk;

void dfs(int u) {
    num[u] = low[u] = ++timer;
    stk.push(u);
    for (int v : adj[u]) {
        if (num[v] != 0) low[u] = min(low[u], num[v]);
        else {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if (low[u] == num[u]) {
        _n++;
        int v = 0;
        while (u != v) {
            v = stk.top();
            num[v] = n + 1;
            d[v] = _n;
            g[_n].push_back(v);
            stk.pop();
        }
    }
    return;
}

void sol() {
    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int u = 1; u <= n; u++) if (num[u] == 0) dfs(u);
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (d[u] == d[v]) continue;
            comp[d[u]].push_back(d[v]);
        }
    }
    for (int u = 1; u <= _n; u++) {
        vector<bool> check(_n + 1, false);
        vector<int> tmp;
        for (int v : comp[u]) {
            if (check[v]) continue;
            tmp.push_back(v);
            check[v] = true;
        }
        comp[u] = tmp;
    }
    cout << _n << "\n\n";
    for (int u = 1; u <= _n; u++) {
        cout << u << " | ";
        for (int v : g[u]) {
            cout << v << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for (int u = 1; u <= _n; u++) {
        for (int v : comp[u]) {
            cout << u << " " << v << "\n";
        }
    }
    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("condensation_graph.inp", "r", stdin);
    // freopen("condensation_graph.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}