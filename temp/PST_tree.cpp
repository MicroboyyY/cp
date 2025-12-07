//find kth smallest number in path u to v
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 9, M = 21;
int V[N], root[N], a[N];
vector<int> g[N];
int par[N][M], dep[N];
void dfsu(int u, int p)
{
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    for (int i = 1; i < M; i++)
    {
        par[u][i] = par[par[u][i - 1]][i - 1];
    }
    for (auto v : g[u])
    {
        if (v != p)
        {
            dfsu(v, u);
        }
    }
}

int lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    int diff = dep[u] - dep[v];
    for (int i = 0; i < M; i++)
    {
        if (diff & (1 << i))
            u = par[u][i];
    }
    if (u == v)
        return u;
    for (int i = M - 1; i >= 0; i--)
    {
        if (par[u][i] != par[v][i])
        {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

struct PST
{
#define lc t[cur].l
#define rc t[cur].r
    struct node
    {
        int l = 0, r = 0, val = 0;
    } t[40 * N];
    int T = 0;
    int build(int b, int e)
    {
        int cur = ++T;
        if (b == e)
            return cur;
        int mid = b + e >> 1;
        lc = build(b, mid);
        rc = build(mid + 1, e);
        t[cur].val = t[lc].val + t[rc].val;
        return cur;
    }
    int upd(int pre, int b, int e, int i, int v)
    {
        int cur = ++T;
        t[cur] = t[pre];
        if (b == e)
        {
            t[cur].val += v;
            return cur;
        }
        int mid = b + e >> 1;
        if (i <= mid)
        {
            rc = t[pre].r;
            lc = upd(t[pre].l, b, mid, i, v);
        }
        else
        {
            lc = t[pre].l;
            rc = upd(t[pre].r, mid + 1, e, i, v);
        }
        t[cur].val = t[lc].val + t[rc].val;
        return cur;
    }
    int query(int up, int le, int pre, int cur, int b, int e, int k)
    {
        if (b == e)
            return b;
        int cnt = t[t[cur].l].val + t[t[pre].l].val - t[t[up].l].val - t[t[le].l].val;
        int mid = (b + e) >> 1;
        if (cnt >= k)
            return query(t[up].l, t[le].l, t[pre].l, lc, b, mid, k);
        else
            return query(t[up].r, t[le].r, t[pre].r, rc, mid + 1, e, k - cnt);
    }
} t;

// the code returns k-th number in a range l to r if the range were sorted

int32_t main()
{
    map<int, int> mp;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i], mp[a[i]];
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfsu(1, 0);
    int c = 0;
    for (auto x : mp)
        mp[x.first] = ++c, V[c] = x.first;
    root[0] = t.build(1, n);
    function<void(int, int)> dfs = [&](int u, int p)
    {
        root[u] = t.upd(root[p], 1, n, mp[a[u]], 1);
        for (auto v : g[u])
            if (v != p)
                dfs(v, u);
    };
    dfs(1, 0);
    while (q--)
    {
        int u, v, k;
        cin >> u >> v >> k;
        int l = lca(u, v);
        int up = par[l][0];
        int x = t.query(root[up], root[l], root[u], root[v], 1, n, k);
        cout << V[x] << "\n";
    }
    return 0;
}