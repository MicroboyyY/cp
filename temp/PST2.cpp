#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 9;
// no of elements sum less than equal to k in l to r
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
    int query(int pre, int cur, int b, int e, int k)
    {
        if (k <= 0)
            return 0;
        if (e <= k)
        {
            return t[cur].val - t[pre].val;
        }
        if (b == e)
            return t[cur].val - t[pre].val;
        int mid = (b + e) >> 1;
        int x = query(t[pre].l, t[cur].l, b, mid, k);
        if (k > mid)
            x += query(t[pre].r, t[cur].r, mid + 1, e, k);
        return x;
    }
} t;

int V[N], root[N], a[N];
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    map<int, int> mp;
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], mp[a[i]];
    int c = 0;
    for (auto x : mp)
        mp[x.first] = ++c, V[c] = x.first;
    root[0] = t.build(1, n);
    for (int i = 1; i <= n; i++)
    {
        root[i] = t.upd(root[i - 1], 1, n, mp[a[i]], a[i]);
    }
    cin >> q;
    int res = 0;
    while (q--)
    {
        int l, r, k;
        cin >> l >> r >> k;
        l ^= res, r ^= res, k ^= res;
        k = upper_bound(V + 1, V + 1 + c, k) - V - 1;
        res = t.query(root[l - 1], root[r], 1, n, k);
        cout << res << '\n';
    }
    return 0;
}