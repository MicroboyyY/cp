#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct Trie
{
    static const int B = 26;
    struct node
    {
        node *nxt[26];
        int sz, islast, dep;
        multiset<int> st;
        node()
        {
            for (int i = 0; i < 26; i++)
                nxt[i] = NULL;
            sz = 0;
            islast = 0;
            dep = 0;
        }
    } *root;
    Trie()
    {
        root = new node();
    }
    void insert(string s)
    {
        node *cur = root;
        cur->sz++;
        for (int i = 0; i < s.size(); i++)
        {
            int b = s[i] - 'a';
            if (cur->nxt[b] == NULL)
                cur->nxt[b] = new node();
            int d = cur->dep;
            cur = cur->nxt[b];
            cur->dep = d + 1;
            cur->sz++;
        }
        cur->islast = 1;
    }
} t;
int n, res = 0;
void dfs(Trie::node *cur)
{
    for (int i = 0; i < 26; i++)
    {
        if (cur->nxt[i])
        {
            dfs(cur->nxt[i]);
            auto &ms = cur->st;
            auto &child_ms = cur->nxt[i]->st;
            if (ms.size() < child_ms.size())
                swap(ms, child_ms);
            for (auto x : child_ms)
                ms.insert(x);
            child_ms.clear();
        }
    }
    if (cur->islast)
        cur->st.insert(cur->dep);
    if (cur->st.size() and !cur->islast and cur != t.root)
    {
        auto it = cur->st.end();
        it--;
        res -= *it - cur->dep;
        cur->st.erase(it);
        cur->st.insert(cur->dep);
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        res += s.size();
        t.insert(s);
    }
    dfs(t.root);
    cout << res << "\n";
    return 0;
}