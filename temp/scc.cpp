#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
const int N = 2e5 + 8;
vector<int> g[N], rg[N];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    f(i, m)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    vector<int> vis(n + 1, 0);
    vector<int> order;
    function<void(int)> dfs = [&](int u)
    {
        vis[u] = 1;
        for (int v : g[u])
        {
            if (!vis[v])
                dfs(v);
        }
        order.push_back(u);
    };
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
            dfs(i);
    }
    vector<int> comp(n + 1, 0);
    function<void(int, int)> dfs2 = [&](int u, int c)
    {
        comp[u] = c;
        for (int v : rg[u])
        {
            if (!comp[v])
                dfs2(v, c);
        }
    };
    int c = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int u = order[i];
        if (!comp[u])
            dfs2(u, ++c);
    }
    cout << c << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << comp[i] << " ";
    }
    return 0;
}