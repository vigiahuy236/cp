/**
 *    author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

//-----------------------------------MAIN------------------------------------//

const int NUMNODE = 1e6 + 5;
const int ALPHSIZE = 26;

struct Trie {
    struct Node { 
        int child[ALPHSIZE];
        int exist; // Number of strings ending at this node
        int cnt; // Number of strings passing through this node (prefix count)
    } nodes[NUMNODE];

    int cur;

    Trie() { 
        _clear_();
    }

    void _clear_() { // Reset the Trie to its initial state
        cur = 0;
        memset(nodes[0].child, -1, sizeof(nodes[0].child));
        nodes[0].exist = 0;
        nodes[0].cnt = 0;
    }

    int _new_node_() { // Initialize a new node and return its index 
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = 0; 
        nodes[cur].cnt = 0;
        return cur;
    }

    void _add_(string s) { // Insert string s into the Trie
        int pos = 0;
        for (char c : s) {
            int x = c - 'a';
            if (nodes[pos].child[x] == -1) { 
                nodes[pos].child[x] = _new_node_();
            }
            pos = nodes[pos].child[x];
            nodes[pos].cnt++; 
        }
        nodes[pos].exist++; 
    }

    bool _del_recur_(int pos, string& s, int i) { // Recursive helper to delete string s and clean up unused nodes
        if (i != (int)s.size()) { 
            int x = s[i] - 'a';
            bool isdel = _del_recur_(nodes[pos].child[x], s, i + 1);
            if (isdel) nodes[pos].child[x] = -1; 
        }
        else nodes[pos].exist--; 
        if (pos != 0) { 
            nodes[pos].cnt--;
            if (nodes[pos].cnt == 0) return true;
        }
        return false;
    }

    void _del_(string s) { // Remove one instance of string s from the Trie
        if (_find_(s) == false) return; 
        _del_recur_(0, s, 0);
    }

    bool _find_(string s) { // Check if string s exists in the Trie
        int pos = 0;
        for (char c : s) {
            int x = c - 'a';
            if (nodes[pos].child[x] == -1) return false;
            pos = nodes[pos].child[x];
        }
        return (nodes[pos].exist != 0); 
    }

    int _cnt_exact_(string s) { // Return the number of times string s was inserted
        int pos = 0;
        for (char c : s) {
            int x = c - 'a';
            if (nodes[pos].child[x] == -1) return 0;
            pos = nodes[pos].child[x];
        }
        return nodes[pos].exist;
    }

    int _cnt_pre_(string s) { // Return the number of strings that have s as a prefix
        int pos = 0;
        for (char c : s) {
            int x = c - 'a';
            if (nodes[pos].child[x] == -1) return 0;
            pos = nodes[pos].child[x];
        }
        return nodes[pos].cnt;
    }
};

//---------------------------------------------------------------------------//


//----------------------------------EXAMPLE----------------------------------//

Trie tr; // Static allocation to avoid stack overflow

void sol() {
    // Example usage of the Trie data structure
    tr._add_("apple");
    tr._add_("apple");
    tr._add_("app");
    tr._add_("apply");

    cout << "--- Initial Trie ---" << "\n";
    cout << "Find 'apple': " << (tr._find_("apple") ? "Found" : "Not Found") << "\n"; // Found
    cout << "Count exact 'apple': " << tr._cnt_exact_("apple") << "\n"; // 2
    cout << "Count prefix 'app': " << tr._cnt_pre_("app") << "\n"; // 4 (apple, apple, app, apply)

    tr._del_("apple");
    cout << "\n--- After deleting one 'apple' ---" << "\n";
    cout << "Count exact 'apple': " << tr._cnt_exact_("apple") << "\n"; // 1
    cout << "Count prefix 'app': " << tr._cnt_pre_("app") << "\n"; // 3

    tr._del_("app");
    cout << "\n--- After deleting 'app' ---" << "\n";
    cout << "Find 'app': " << (tr._find_("app") ? "Found" : "Not Found") << "\n"; // Not Found
    cout << "Count prefix 'app': " << tr._cnt_pre_("app") << "\n"; // 2 (apple, apply)

    return;
}

//---------------------------------------------------------------------------//

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("trie.inp", "r", stdin);
    // freopen("trie.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}