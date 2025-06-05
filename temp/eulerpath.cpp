#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
const int N = 2e5 + 9;
vector<int> g[N], ans;
int vis[N], indeg[N], outdeg[N];
int n, m;
void dfs(int u)
{
    while (g[u].size())
    {
        int v = g[u].back();
        g[u].pop_back();
        dfs(v);
    }
    ans.push_back(u);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    // euler path
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
        outdeg[u]++;
    }
    int c = 0, f = 0, f2 = 0;
    for (int i = 2; i < n; i++)
    {
        if (indeg[i] != outdeg[i])
        {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    if ((outdeg[1] - indeg[1] != 1) or (indeg[n] - outdeg[n] != 1))
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    dfs(1);
    if (ans.size() != m + 1)
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    reverse(all(ans));
    for (auto x : ans)
        cout << x << ' ';
    return 0;
}