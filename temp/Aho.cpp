// find all pos in text where s occure
#include <bits/stdc++.h>
using namespace std;

struct AC
{
    static const int A = 26;
    struct Node
    {
        int nxt[A], link = 0;
        vector<int> out;
        Node() { memset(nxt, 0, sizeof nxt); }
    };
    vector<Node> t;
    vector<int> order;
    AC() { t.emplace_back(); }
    inline int id(char c) { return c - 'a'; }
    void add(const string &s, int pid)
    {
        int u = 0;
        for (char c : s)
        {
            int x = id(c);
            if (!t[u].nxt[x])
            {
                t[u].nxt[x] = t.size();
                t.emplace_back();
            }
            u = t[u].nxt[x];
        }
        t[u].out.push_back(pid);
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
            order.push_back(u);
            int f = t[u].link;
            for (int c = 0; c < A; c++)
            {
                int v = t[u].nxt[c];
                if (v)
                {
                    t[v].link = t[f].nxt[c];
                    q.push(v);
                }
                else
                    t[u].nxt[c] = t[f].nxt[c];
            }
        }
        for (int v : order)
        {
            int f = t[v].link;
            if (!t[f].out.empty())
                t[v].out.insert(t[v].out.end(), t[f].out.begin(), t[f].out.end());
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<int> k(n);
    vector<string> m(n);
    for (int i = 0; i < n; i++)
        cin >> k[i] >> m[i];

    AC ac;
    vector<int> L(n);
    for (int i = 0; i < n; i++)
    {
        L[i] = m[i].size();
        ac.add(m[i], i);
    }
    ac.build();

    vector<vector<int>> pos(n);
    int u = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
        u = ac.t[u].nxt[s[i] - 'a'];
        for (int pid : ac.t[u].out)//jei jei string er idx a ses hoise tader idx
        {
            int st = i - L[pid] + 1;
            if (st >= 0)
                pos[pid].push_back(st);
        }
    }

    for (int i = 0; i < n; i++)
    {
        auto &v = pos[i];
        int need = k[i];
        if ((int)v.size() < need)
        {
            cout << -1 << "\n";
            continue;
        }
        int best = INT_MAX;
        int len = L[i];
        for (int j = 0; j + need - 1 < (int)v.size(); j++)
            best = min(best, v[j + need - 1] - v[j] + len);
        cout << best << "\n";
    }
    return 0;
}
