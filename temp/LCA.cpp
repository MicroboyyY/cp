#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
const int N = 2e5 + 5, M = 20;
vector<int> g[N];
int n, q;
int par[N][M], arr[N], dep[N], minVal[N][M];

void dfs(int u, int p)
{
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    minVal[u][0] = arr[u];
    for (int i = 1; i < M; i++)
    {
        par[u][i] = par[par[u][i - 1]][i - 1];
        minVal[u][i] = min(minVal[u][i - 1], minVal[par[u][i - 1]][i - 1]);
    }
    for (auto v : g[u])
    {
        if (v != p)
        {
            dfs(v, u);
        }
    }
}

int lca(int u, int v)
{
    int minResult = INT_MAX;
    if (dep[u] < dep[v])
        swap(u, v);
    int diff = dep[u] - dep[v];
    for (int j = 19; j >= 0; j--)
    {
        if (diff >> j & 1)
        {
            minResult = min(minResult, minVal[u][j]);
            u = par[u][j];
        }
    }
    if (u == v)
        return min(minResult, arr[u]);
    for (int j = 19; j >= 0; j--)
    {
        if (par[u][j] != par[v][j])
        {
            minResult = min({minResult, minVal[u][j], minVal[v][j]});
            u = par[u][j];
            v = par[v][j];
        }
    }
    minResult = min({minResult, arr[u], arr[v], arr[par[u][0]]});
    return minResult;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        g[x].push_back(i);
        g[i].push_back(x);
    }
    dfs(1, 0);
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
}
