#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
const int N = 2e5 + 5, M = 20;
vector<int> g[N];
int n, q;
pair<int, int> par[N][M]; // {parent, min_weight}
int arr[N], dep[N];

void dfs(int u, int p)
{
    for (int i = 0; i < M; i++)
        par[u][i] = {0, INT_MAX};

    par[u][0] = {p, (p == 0 ? arr[u] : min(arr[u], arr[p]))};
    dep[u] = dep[p] + 1;

    for (int i = 1; i < M; i++)
    {
        int ancestor = par[u][i - 1].first;
        par[u][i] = {par[ancestor][i - 1].first, min(par[u][i - 1].second, par[ancestor][i - 1].second)};
    }

    for (auto v : g[u])
    {
        if (v != p)
        {
            dfs(v, u);
        }
    }
}

int MinDist(int u, int v)
{
    int mn = INT_MAX;
    if (dep[u] < dep[v])
        swap(u, v);

    int diff = dep[u] - dep[v];
    for (int j = M - 1; j >= 0; j--)
    {
        if ((diff >> j) & 1)
        {
            mn = min(mn, par[u][j].second);
            u = par[u][j].first;
        }
    }

    if (u == v)
        return min(mn, arr[u]);

    for (int j = M - 1; j >= 0; j--)
    {
        if (par[u][j].first != par[v][j].first)
        {
            mn = min(mn, min(par[u][j].second, par[v][j].second));
            u = par[u][j].first;
            v = par[v][j].first;
        }
    }

    // Include the minimum weight of the final ancestors
    return min({mn, arr[u], arr[v], par[u][0].second, par[v][0].second});
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i]; // each node value
    }

    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        g[x].push_back(i);
        g[i].push_back(x);
    }

    dep[0] = -1;
    dfs(1, 0);

    while (q--)
    {
        int u, v;
        cin >> u >> v;
        cout << MinDist(u, v) << '\n';
    }
}