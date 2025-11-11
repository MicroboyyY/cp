#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 9;
vector<int> g[N], vecBag[N];
int n, col[N], sz[N], cnt[N], ans[N], dist;
bool bigC[N];

void dfs(int v, int p)
{
    sz[v] = 1;
    for (int u : g[v])
        if (u != p)
        {
            dfs(u, v);
            sz[v] += sz[u];
        }
}

void add(int v, int p, int x)
{
    int c = col[v];
    int b = cnt[c];
    cnt[c] += x;
    int a = cnt[c];
    if (b == 0 && a > 0)
        ++dist;
    else if (b > 0 && a == 0)
        --dist;
    for (int u : g[v])
        if (u != p && !bigC[u])
            add(u, v, x);
}

void dsu(int v, int p, bool keep)
{
    int big = -1, mx = -1;
    for (int u : g[v])
        if (u != p)
        {
            if (sz[u] > mx)
                mx = sz[u], big = u;
        }
    for (int u : g[v])
        if (u != p && u != big)
            dsu(u, v, false);
    if (big != -1)
    {
        dsu(big, v, true);
        bigC[big] = true;
        swap(vecBag[v], vecBag[big]);
    }
    vecBag[v].push_back(v);
    for (int u : g[v])
        if (u != p && u != big)
            for (int x : vecBag[u])
                vecBag[v].push_back(x);
    add(v, p, 1);
    ans[v] = dist;
    if (big != -1)
        bigC[big] = false;
    if (!keep)
    {
        add(v, p, -1);
        vecBag[v].clear();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> col[i];
    vector<int> vals;
    vals.reserve(n);
    for (int i = 1; i <= n; i++)
        vals.push_back(col[i]);
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

    dfs(1, 0);
    dsu(1, 0, 0);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    return 0;
}