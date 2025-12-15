// kth dist kjnlexo min substr
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 9;

struct SuffixAutomaton
{
    struct node
    {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last;
    vector<node> t;
    vector<int> terminal;
    vector<long long> dp;
    vector<vector<int>> g;
    SuffixAutomaton() {}
    SuffixAutomaton(int n)
    {
        t.resize(2 * n);
        terminal.resize(2 * n, 0);
        dp.resize(2 * n, -1);
        sz = 1;
        last = 0;
        g.resize(2 * n);
        t[0].len = 0;
        t[0].link = -1;
        t[0].firstpos = 0;
    }
    void extend(char c)
    {
        int p = last;
        if (t[p].nxt.count(c))
        {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1)
            {
                last = q;
                return;
            }
            int clone = sz++;
            t[clone] = t[q];
            t[clone].len = t[p].len + 1;
            t[q].link = clone;
            last = clone;
            while (p != -1 && t[p].nxt[c] == q)
            {
                t[p].nxt[c] = clone;
                p = t[p].link;
            }
            return;
        }
        int cur = sz++;
        t[cur].len = t[last].len + 1;
        t[cur].firstpos = t[cur].len;
        p = last;
        while (p != -1 && !t[p].nxt.count(c))
        {
            t[p].nxt[c] = cur;
            p = t[p].link;
        }
        if (p == -1)
            t[cur].link = 0;
        else
        {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len)
                t[cur].link = q;
            else
            {
                int clone = sz++;
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                while (p != -1 && t[p].nxt[c] == q)
                {
                    t[p].nxt[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        last = cur;
    }
    void build_tree()
    {
        for (int i = 1; i < sz; i++)
            g[t[i].link].push_back(i);
    }
    void build(string &s)
    {
        for (auto x : s)
        {
            extend(x);
            terminal[last] = 1;
        }
        build_tree();
    }
    long long cnt(int i)
    {
        if (dp[i] != -1)
            return dp[i];
        long long ret = terminal[i];
        for (auto &x : g[i])
            ret += cnt(x);
        return dp[i] = ret;
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    while (t--)
    {
        string s, res;
        cin >> s;
        int k, n = s.size();
        cin >> k;

        SuffixAutomaton sa(n);
        sa.build(s);
        // no of unique substring
        //  int ans=0;
        //  for (int i = 1; i < sa.sz; i++) ans += sa.t[i].len - sa.t[sa.t[i].link].len;

        vector<int> cntLen(n + 1, 0), order(sa.sz);
        for (int i = 0; i < sa.sz; i++)
            cntLen[sa.t[i].len]++;
        for (int i = 1; i <= n; i++)
            cntLen[i] += cntLen[i - 1];
        for (int i = sa.sz - 1; i >= 0; i--)
            order[--cntLen[sa.t[i].len]] = i;

        vector<int> dp2(sa.sz, 0);
        for (int idx = sa.sz - 1; idx >= 0; idx--)
        {
            int v = order[idx];
            int sum = 0;
            for (auto &e : sa.t[v].nxt)
            {
                int to = e.second;
                sum += dp2[to] + 1;
            }
            dp2[v] = sum;
        }

        int node = 0;
        while (k > 0)
        {
            for (char c = 'a'; c <= 'z'; c++)
            {
                auto it = sa.t[node].nxt.find(c);
                if (it == sa.t[node].nxt.end())
                    continue;
                int to = it->second;
                int block = dp2[to] + 1;
                if (k > block)
                {
                    k -= block;
                }
                else
                {
                    res.push_back(c);
                    k--;
                    node = to;
                    break;
                }
            }
        }

        cout << res << '\n';
    }
    return 0;
}
