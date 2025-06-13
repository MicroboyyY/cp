#include <bits/stdc++.h>
using namespace std;

bool dfs(int v, const vector<vector<int>> &adj,
         vector<int> &path, vector<char> &used)
{
    if (path.size() + 1 == adj.size())
        return true;
    for (int u : adj[v])
        if (!used[u])
        {
            used[u] = 1;
            path.push_back(u);
            if (dfs(u, adj, path, used))
                return true;
            path.pop_back();
            used[u] = 0;
        }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        if (N == 2 || N == 3 || N == 4 || N == 6)
        {
            cout << -1 << '\n';
            continue;
        }

        vector<vector<int>> adj(N + 1);
        for (int i = 1; i <= N; ++i)
            for (int j = i + 1; j <= N; ++j)
                if (abs(i - j) > 1 && gcd(i, j) == 1)
                {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
        for (int v = 1; v <= N; ++v)
            sort(adj[v].begin(), adj[v].end(),
                 [&](int a, int b)
                 { return adj[a].size() < adj[b].size(); });

        vector<char> used(N + 1, 0);
        vector<int> path;
        path.reserve(N);
        path.push_back(1);
        used[1] = 1;

        if (!dfs(1, adj, path, used))
        {
            cout << -1 << '\n';
            continue;
        }
        for (int i = 0; i < N; ++i)
            cout << path[i] << " \n"[i == N - 1];
    }
    return 0;
}
