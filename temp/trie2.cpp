#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 9;

struct Trie
{
    static const int B = 50;
    struct node
    {
        node *nxt[2];
        int sz;
        node()
        {
            nxt[0] = nxt[1] = NULL;
            sz = 0;
        }
    } *root;
    Trie()
    {
        root = new node();
    }
    void insert(int val)
    {
        node *cur = root;
        cur->sz++;
        for (int i = B - 1; i >= 0; i--)
        {
            int b = val >> i & 1ll;
            if (cur->nxt[b] == NULL)
                cur->nxt[b] = new node();
            cur = cur->nxt[b];
            cur->sz++;
        }
    }
    void del(int val)
    {
        node *cur = root;
        cur->sz--;
        for (int i = B - 1; i >= 0; i--)
        {
            int b = val >> i & 1ll;
            cur = cur->nxt[b];
            cur->sz--;
        }
    }
    int get_max(int x)
    { // returns maximum of val ^ x
        node *cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--)
        {
            int k = x >> i & 1ll;
            if (cur->nxt[!k] && cur->nxt[!k]->sz > 0)
                cur = cur->nxt[!k], ans = (ans << 1ll) | 1ll;
            else
                cur = cur->nxt[k], ans <<= 1ll;
        }
        return ans;
    }
} t;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n + 1), px(n + 1), sx(n + 1);
    t.insert(0);
    for (int i = 1; i <= n; i++)
        cin >> v[i], px[i] = (px[i - 1] ^ v[i]), t.insert(px[i]);
    int ans = 0, x = 0;
    for (int i = n; i >= 1; i--)
    {
        x ^= v[i];
        t.del(px[i]);
        ans = max(ans, t.get_max(x));
        sx[i] = x;
    }
    for (int i = 1; i <= n; i++)
        t.insert(sx[i]);
    x = 0;
    for (int i = 1; i <= n; i++)
    {
        x ^= v[i];
        t.del(sx[i]);
        ans = max(ans, t.get_max(x));
    }
    cout << ans << "\n";

    return 0;
}