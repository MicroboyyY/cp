#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
vector<int> ans;
vector<vector<int>> g;
void dfs(int u)
{
    while (g[u].size())
    {
        int v = g[u].back();
        g[u].pop_back();
        dfs(v);
    }
    ans.push_back(u & 1);
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    g.resize(1 << n);
    for (int node = 0; node < (1 << (n - 1)); node++)
    {
        int v = (node << 1) & ((1 << (n - 1)) - 1);
        g[node].push_back(v);
        g[node].push_back(v + 1);
    }
    dfs(0);
    if (n == 1)
    {
        cout << "10\n";
        return 0;
    }
    for (int i = 0; i < n - 2; i++)
    {
        ans.push_back(0);
    }
    for (auto x : ans)
        cout << x;
}