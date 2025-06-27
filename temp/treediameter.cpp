#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'

const int N = 200005;
int n;
vector<vector<int>> g;
int par[N], c = 1;
pair<int, int> dfs(int node, int parent)
{
    int bestDist = 0, bestNode = node;
    if (c == 2)
        par[node] = parent;
    for (int v : g[node])
        if (v != parent)
        {
            auto [d, u] = dfs(v, node);
            if (d + 1 > bestDist)
            {
                bestDist = d + 1;
                bestNode = u;
            }
        }
    return {bestDist, bestNode};
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        g.clear();
        g.assign(n + 1, {});
        c = 1;
        fill(par, par + n + 1, -1);

        for (int i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        auto [d, u] = dfs(1, -1);
        c++;
        auto [diam, v] = dfs(u, -1);
        // cout << u << ' ' << v << ' ' << diam << '\n';
        vector<int> path;
        while (par[v] != -1)
        {
            path.push_back(v);
            v = par[v];
        }
        path.push_back(v);
        for (auto x : path)
            cout << x << ' ';
    }
}
