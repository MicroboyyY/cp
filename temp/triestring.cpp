#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 9;

struct Trie
{
    static const int B = 26;
    struct node
    {
        node *nxt[26];
        int sz, flag;
        node()
        {
            for (int i = 0; i < 26; i++)
                nxt[i] = NULL;
            sz = 0;
            flag = 0;
        }
    } *root;
    Trie()
    {
        root = new node();
    }
    void insert(string &s)
    {
        node *cur = root;
        for (int i = 0; i < s.size(); i++)
        {
            int c = s[i] - 'a';
            if (cur->nxt[c] == NULL)
                cur->nxt[c] = new node();
            cur = cur->nxt[c];
            cur->sz++;
        }
        cur->flag = 1;
    }
    int search(string &s)
    {
        node *cur = root;
        for (int i = 0; i < s.size(); i++)
        {
            int c = s[i] - 'a';
            if (cur->nxt[c] == NULL)
                return 0;
            cur = cur->nxt[c];
        }
        return cur->sz;
    }
} t;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    int cur = 0;
    while (n--)
    {
        string s;
        cin >> s;
        t.insert(s);
    }
    while (q--)
    {
        string s;
        cin >> s;
        cout << t.search(s) << endl;
    }

    return 0;
}