#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
const int N = 2e5 + 7;
vector<int> g[N];
vector<pair<int, int>> bridge;
int sz[N], n, m, vis[N], disc[N], low[N], timer;
void dfs(int u, int p)
{
    vis[u] = 1;
    disc[u] = low[u] = ++timer;
    for (int v : g[u])
    {
        if (v == p)
            continue;
        if (!vis[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
            {
                bridge.push_back({u, v});
            }
        }
        else
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}
int nc2(int n)
{
    return n * (n - 1) / 2;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        bridge.clear();
        f(i, n + 1) sz[i] = 0, g[i].clear(), vis[i] = 0, disc[i] = -1, low[i] = -1;
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        timer = 0;
        dfs(1, -1); // O(V+E)
        for (auto [u, v] : bridge)
        {
            cout << u << " " << v << endl;
        }
    }
}