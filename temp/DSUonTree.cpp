#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;
vector<int> g[N];
int ans[N], col[N], sz[N], cnt[N], n, dist;
bool big[N];
void dfs(int u, int p)
{
    sz[u] = 1;
    for (auto v : g[u])
    {
        if (v == p)
            continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
void add(int u, int p, int x)
{
    int c = col[u];
    int before = cnt[c];
    cnt[c] += x;
    int after = cnt[c];
    if (before == 0 && after > 0)
        dist++;
    else if (before > 0 && after == 0)
        dist--;
    for (auto v : g[u])
    {
        if (v == p || big[v] == 1)
            continue;
        add(v, u, x);
    }
}
void dsu(int u, int p, bool keep)
{
    int bigchild = -1, mx = -1;
    for (auto v : g[u])
    {
        if (v == p)
            continue;
        if (sz[v] > mx)
            mx = sz[v], bigchild = v;
    }
    for (auto v : g[u])
    {
        if (v == p || v == bigchild)
            continue;
        dsu(v, u, 0);
    }
    if (bigchild != -1)
        dsu(bigchild, u, 1), big[bigchild] = 1;
    add(u, p, 1);
    ans[u] = dist;
    if (bigchild != -1)
        big[bigchild] = 0;
    if (keep == 0)
        add(u, p, -1);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> n;
    vector<int> vals;
    vals.reserve(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> col[i];
        vals.push_back(col[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 1; i <= n; i++)
        col[i] = int(lower_bound(vals.begin(), vals.end(), col[i]) - vals.begin()) + 1;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, -1);
    dsu(1, -1, 0);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";

    return 0;
}