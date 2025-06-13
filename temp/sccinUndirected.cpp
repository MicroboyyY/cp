#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define fi first
#define se second
#define pb push_back
#define sz(v) (int)v.size()
#define all(v) v.begin(), v.end()

using ll = long long;
using ii = pair<ll, ll>;

const int N = 2e5 + 10;
const int MOD = 1e9 + 7;

int n, m;
vector<int> g[N];

int cyc[N], vis[N], par[N];
void visit(int u, int f)
{
    vis[u] = 1, par[u] = f, cyc[u] = u;
    for (int v : g[u])
        if (v != f)
        {
            if (vis[v] && cyc[u] == u)
            {
                int _u = u;
                ++n;
                while (_u != par[v])
                {
                    cyc[_u] = n;
                    _u = par[_u];
                }
            }
            else if (!vis[v])
                visit(v, u);
        }
}

int p[18][N], lev[N], c[N];
void dfs(int u, int f)
{
    p[0][u] = f, c[u] = (u > n) + c[f], lev[u] = lev[f] + 1;
    for (int j = 1; j < 18; j++)
        p[j][u] = p[j - 1][p[j - 1][u]];

    for (int v : g[u])
        if (v != f)
        {
            dfs(v, u);
        }
}

int lca(int u, int v)
{
    if (lev[u] > lev[v])
        swap(u, v);
    for (int j = 17; j >= 0; j--)
        if (lev[v] - (1 << j) >= lev[u])
            v = p[j][v];
    if (u == v)
        return u;
    for (int j = 17; j >= 0; j--)
        if (p[j][u] != p[j][v])
            u = p[j][u], v = p[j][v];
    return p[0][u];
}

int cnt(int u, int v)
{
    int p = lca(u, v);
    return c[u] + c[v] - 2 * c[p] + (p > n);
}

ll powmod(ll a, ll b, ll r = 1)
{
    while (b)
    {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].pb(v);
        g[v].pb(u);
    }
    int _n = n;
    visit(1, 0);
    for (int u = 1; u <= _n; u++)
    {
        if (cyc[u] == u)
        {
            for (int &v : g[u])
                v = cyc[v];
        }
        else if (cyc[u] != u)
        {
            for (int &v : g[u])
                if (cyc[v] != cyc[u])
                    g[cyc[u]].pb(cyc[v]);
            g[u].clear();
        }
    }

    int root = n;
    n = _n;
    dfs(root, 0);
    for (int i = 1; i <= n; i++)
        cout << cyc[i] << " ";
    cout << endl;
    return 0;
}
