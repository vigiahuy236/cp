/**
 *    author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
int n;
string s;
int pi[N]; 

void sol() {
    cin >> s;
    n = s.size();
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j; 
    }
    for (int i = 1; i <= n; i++) cout << pi[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("KMP.inp", "r", stdin);
    // freopen("KMP.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}