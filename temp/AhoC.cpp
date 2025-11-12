#include <bits/stdc++.h>
using namespace std;

struct AC
{
    static const int A = 26, N = 500005;
    struct Node
    {
        int nxt[A];
        int link = 0;
        vector<int> out;
        Node() { memset(nxt, 0, sizeof nxt); }
    };
    vector<Node> t;
    vector<int> bfs_order;
    AC()
    {
        t.reserve(N);
        t.emplace_back();
    }
    inline int idx(char ch) const { return ch - 'a'; }
    void add(const string &s, int id)
    {
        int u = 0;
        for (char ch : s)
        {
            int c = idx(ch);
            if (!t[u].nxt[c])
            {
                t[u].nxt[c] = (int)t.size();
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
            bfs_order.push_back(u);
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

    vector<long long> cnt(ac.t.size(), 0);
    int u = 0;
    for (char ch : text)
    {
        if (ch < 'a' || ch > 'z')
        {
            u = 0;
            continue;
        }
        u = ac.t[u].nxt[ch - 'a'];
        cnt[u]++;
    }

    for (int i = (int)ac.bfs_order.size() - 1; i >= 0; --i)
    {
        int v = ac.bfs_order[i];
        int f = ac.t[v].link;
        cnt[f] += cnt[v];
    }

    vector<long long> ans(n, 0);
    for (int v = 0; v < (int)ac.t.size(); v++)
        for (int id : ac.t[v].out)
            ans[id] += cnt[v];

    for (int i = 0; i < n; i++)
        cout << ans[i] << '\n';
    return 0;
}
