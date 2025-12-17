#include <bits/stdc++.h>
using namespace std;
/*
    MODE = 0 -> print FIRST occurrence position (1-indexed) for each pattern (or -1)
    MODE = 1 -> print ALL occurrence positions (1-indexed) for each pattern (or -1)

    Note: MODE = 1 can be very large output -> printing itself may TLE if matches are huge.
*/
struct AC
{
    static const int A = 26;

    struct Node
    {
        int nxt[A];
        int link = 0;    // failure link
        vector<int> out; // pattern ids that END at this node (only terminal ids)
        Node() { memset(nxt, 0, sizeof nxt); }
    };

    vector<Node> t;
    vector<int> bfs_order; // BFS order (excluding root)
    vector<int> out_link;  // jump along failure chain to next node having out (for ALL matches)
    vector<int> plen;      // pattern lengths

    AC(int reserveN = 0)
    {
        if (reserveN)
            t.reserve(reserveN);
        t.emplace_back(); // root
    }

    inline int idx(char ch) const { return ch - 'a'; }

    void add(const string &s, int id)
    {
        int u = 0;
        for (char ch : s)
        {
            int c = idx(ch);
            if (!t[u].nxt[c])
            {
                t[u].nxt[c] = (int)t.size();
                t.emplace_back();
            }
            u = t[u].nxt[c];
        }
        t[u].out.push_back(id);
    }

    // need_out_link = true only if you want ALL occurrences (MODE=1)
    void build(bool need_out_link)
    {
        queue<int> q;
        bfs_order.clear();
        if (need_out_link)
            out_link.assign(t.size(), 0);

        for (int c = 0; c < A; c++)
        {
            int v = t[0].nxt[c];
            if (v)
                q.push(v);
            else
                t[0].nxt[c] = 0;
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            bfs_order.push_back(u);

            int f = t[u].link;

            // out_link[u] = nearest suffix-state (via failure) that has some terminal patterns
            if (need_out_link)
            {
                out_link[u] = (!t[f].out.empty()) ? f : out_link[f];
            }

            for (int c = 0; c < A; c++)
            {
                int v = t[u].nxt[c];
                if (v)
                {
                    t[v].link = t[f].nxt[c];
                    q.push(v);
                }
                else
                {
                    t[u].nxt[c] = t[f].nxt[c];
                }
            }
        }
    }

    // FIRST occurrence for each pattern id (1-indexed start), -1 if not found
    vector<int> first_occurrence(const string &text, const vector<int> &len)
    {
        const int INF = 1e9;
        vector<int> minEnd(t.size(), INF); // earliest end position (1-based) where state is reached

        int u = 0;
        for (int i = 0; i < (int)text.size(); i++)
        {
            u = t[u].nxt[text[i] - 'a'];
            minEnd[u] = min(minEnd[u], i + 1);
        }

        // If a state v is reached, all its suffix states (via failure) are also reached
        for (int i = (int)bfs_order.size() - 1; i >= 0; --i)
        {
            int v = bfs_order[i];
            int f = t[v].link;
            minEnd[f] = min(minEnd[f], minEnd[v]);
        }

        vector<int> ans((int)len.size(), -1);
        for (int v = 0; v < (int)t.size(); v++)
        {
            if (minEnd[v] == INF)
                continue;
            for (int id : t[v].out)
            {
                int start = minEnd[v] - len[id] + 1; // 1-based start
                if (start >= 1)
                    ans[id] = start;
            }
        }
        return ans;
    }

    // ALL occurrences for each pattern id (1-indexed starts)
    vector<vector<int>> all_occurrences(const string &text, const vector<int> &len)
    {
        vector<vector<int>> occ((int)len.size());
        int u = 0;

        for (int i = 0; i < (int)text.size(); i++)
        {
            u = t[u].nxt[text[i] - 'a'];

            // Walk only output-bearing suffix states using out_link (fast)
            int v = u;
            while (v)
            {
                for (int id : t[v].out)
                {
                    int start = (i + 1) - len[id] + 1; // 1-based start
                    if (start >= 1)
                        occ[id].push_back(start);
                }
                v = out_link[v];
            }
        }
        return occ;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MODE = 0; // 0 = FIRST only, 1 = ALL positions

    string text;
    cin >> text;
    int k;
    cin >> k;

    vector<string> pat(k);
    vector<int> len(k);
    int totalLen = 0;
    for (int i = 0; i < k; i++)
    {
        cin >> pat[i];
        len[i] = (int)pat[i].size();
        totalLen += len[i];
    }

    AC ac(totalLen + 5);
    for (int i = 0; i < k; i++)
        ac.add(pat[i], i);

    if (MODE == 0)
    {
        ac.build(false);
        auto ans = ac.first_occurrence(text, len);
        for (int i = 0; i < k; i++)
            cout << ans[i] << '\n';
    }
    else
    {
        ac.build(true);
        auto occ = ac.all_occurrences(text, len);

        // Output format: each pattern in one line, positions space-separated; if none -> -1
        for (int i = 0; i < k; i++)
        {
            if (occ[i].empty())
            {
                cout << -1 << '\n';
            }
            else
            {
                for (int j = 0; j < (int)occ[i].size(); j++)
                {
                    if (j)
                        cout << occ[i][j] << " ";
                }
                cout << '\n';
            }
        }
    }

    return 0;
}
