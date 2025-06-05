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

/*
https://codeforces.com/problemset/problem/508/D

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
int code(char c)
{
    if ('a' <= c and c <= 'z')
        return c - 'a';
    if ('A' <= c and c <= 'Z')
        return 26 + (c - 'A');
    return 52 + (c - '0');
}
char dec(int x)
{
    if (x < 26)
        return 'a' + x;
    if (x < 52)
        return 'A' + x - 26;
    return '0' + x - 52;
}
int id(int a, int b) { return a * 62 + b; }

const int V = 62 * 62;
vector<vector<int>> adj(V);
vector<int> path;

void dfs(int v)
{
    while (!adj[v].empty())
    {
        int u = adj[v].back();
        adj[v].pop_back();
        dfs(u);
    }
    path.push_back(v);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> in(V), out(V);
    string s;
    for (int i = 0; i < n; ++i)
    {
        cin >> s;
        int u = id(code(s[0]), code(s[1]));
        int v = id(code(s[1]), code(s[2]));
        adj[u].push_back(v);
        out[u]++;
        in[v]++;
    }

    int start = -1, end = -1;
    for (int v = 0; v < V; v++)
    {
        int d = out[v] - in[v];
        if (d == 1)
        {
            if (start != -1)
            {
                cout << "NO\n";
                return 0;
            }
            start = v;
        }
        else if (d == -1)
        {
            if (end != -1)
            {
                cout << "NO\n";
                return 0;
            }
            end = v;
        }
        else if (d != 0)
        {
            cout << "NO\n";
            return 0;
        }
    }
    if (start == -1)
    {
        for (int v = 0; v < V; ++v)
            if (out[v])
            {
                start = v;
                break;
            }
        if (start == -1)
        {
            cout << "NO\n";
            return 0;
        }
    }

    dfs(start);
    if ((int)path.size() != n + 1)
    {
        cout << "NO\n";
        return 0;
    }
    reverse(all(path));
    string res = "";
    res += dec(path[0] / 62);
    res += dec(path[0] % 62);
    for (int i = 1; i < path.size(); ++i)
        res += dec(path[i] % 62);
    cout << "YES\n";
    cout << res << '\n';
}

*/