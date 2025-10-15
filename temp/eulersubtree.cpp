#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 9;
 
int a[N], n, q, intime[N], outtime[N], timer;
struct ST
{
    int t[4 * N];
    static const int inf = 1e9;
    ST()
    {
        memset(t, 0, sizeof t);
    }
    void build(int n, int b, int e, vector<int> &euler)
    {
        if (b == e)
        {
            t[n] = euler[b];
            return;
        }
        int mid = (b + e) >> 1, l = n << 1, r = l | 1;
        build(l, b, mid, euler);
        build(r, mid + 1, e, euler);
        t[n] = (t[l] + t[r]);
    }
    void upd(int n, int b, int e, int i, int x)
    {
        if (b > i || e < i)
            return;
        if (b == e && b == i)
        {
            t[n] = x;
            return;
        }
        int mid = (b + e) >> 1, l = n << 1, r = l | 1;
        upd(l, b, mid, i, x);
        upd(r, mid + 1, e, i, x);
        t[n] = (t[l] + t[r]);
    }
    int query(int n, int b, int e, int i, int j)
    {
        if (b > j || e < i)
            return 0;
        if (b >= i && e <= j)
            return t[n];
        int mid = (b + e) >> 1, l = n << 1, r = l | 1;
        int L = query(l, b, mid, i, j);
        int R = query(r, mid + 1, e, i, j);
        return (L + R);
    }
} t;
 
vector<int> adj[N];
void dfs(int u, int p)
{
    intime[u] = ++timer;
    for (auto v : adj[u])
        if (v != p)
            dfs(v, u);
    outtime[u] = ++timer;
}
 
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, -1);
    vector<int> euler(2 * n + 1);
    for (int i = 1; i <= n; i++)
    {
        euler[intime[i]] = a[i];
        euler[outtime[i]] = a[i];
    }
    t.build(1, 1, 2 * n, euler);
    // for (int i = 1; i <= 2 * n; i++)
    //     cout << euler[i] << " ";
    // cout << endl;
    while (q--)
    {
        int ty;
        cin >> ty;
        if (ty == 1)
        {
            int s, x;
            cin >> s >> x;
            t.upd(1, 1, 2 * n, intime[s], x);
            t.upd(1, 1, 2 * n, outtime[s], x);
        }
        else
        {
            int s;
            cin >> s;
            cout << t.query(1, 1, 2 * n, intime[s], outtime[s])/2 << '\n';
        }
    }
    return 0;
}