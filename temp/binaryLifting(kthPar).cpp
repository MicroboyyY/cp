#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
const int N = 2e5 + 5, M = 30;
int a[N], par[N][M], dep[N], n, q;
vector<int> g[N];
void dfs(int u, int p)
{
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    for (int i = 1; i < M; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != p)
            dfs(v, u);
}
int kth_par(int u, int k)
{
    for (int i = 0; i < M; i++)
        if (k & (1 << i))
            u = par[u][i];
    return u;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
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
        int x, k;
        cin >> x >> k;
        cout << (dep[x] <= k ? -1 : kth_par(x, k)) << '\n';
    }
}