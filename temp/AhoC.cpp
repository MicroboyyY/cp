#include <bits/stdc++.h>
using namespace std;

struct AC
{
    static const int A = 26;
    struct Node
    {
        int nxt[A];
        int link = 0;
        vector<int> out;
        Node() { memset(nxt, 0, sizeof nxt); }
    };
    vector<Node> t;
    AC()
    {
        t.reserve(500000 + 5);
        t.emplace_back();
    }
    void add(const string &s, int id)
    {
        int u = 0;
        for (char ch : s)
        {
            int c = ch - 'a';
            if (!t[u].nxt[c])
            {
                t[u].nxt[c] = t.size();
                t.emplace_back();
            }
            u = t[u].nxt[c];
        }
        t[u].out.push_back(id);
    }
    void build()
    {
        queue<int> q;
        for (int c = 0; c < A; c++)
        {
            int v = t[0].nxt[c];
            if (v)
            {
                t[v].link = 0;
                q.push(v);
            }
            else
                t[0].nxt[c] = 0;
        }
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            int sl = t[u].link;
            for (int c = 0; c < A; c++)
            {
                int v = t[u].nxt[c];
                if (v)
                {
                    t[v].link = t[sl].nxt[c];
                    q.push(v);
                }
                else
                    t[u].nxt[c] = t[sl].nxt[c];
            }
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string text;
    cin >> text;
    int n;
    cin >> n;
    vector<string> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    AC ac;
    for (int i = 0; i < n; i++)
        ac.add(p[i], i);
    ac.build();
    vector<char> seen(n, 0);
    vector<char> used_node(ac.t.size(), 0);
    int u = 0;
    for (char ch : text)
    {
        u = ac.t[u].nxt[ch - 'a'];
        int v = u;
        while (v && !used_node[v])
        {
            for (int id : ac.t[v].out)
                seen[id] = 1;
            used_node[v] = 1;
            v = ac.t[v].link;
        }
    }
    for (int i = 0; i < n; i++)
        cout << (seen[i] ? "YES" : "NO") << '\n';
    return 0;
}
