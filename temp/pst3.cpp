// no of distinct elements in range l to r
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;

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
            t[cur].val = v;
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
    int query(int cur, int b, int e, int l, int r)
    {
        if (r < b || e < l)
            return 0;
        if (l <= b && e <= r)
            return t[cur].val;
        int mid = b + e >> 1;
        return query(lc, b, mid, l, r) + query(rc, mid + 1, e, l, r);
    }
} t;

int V[N], root[N], a[N];
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    map<int, int> mp;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i], mp[a[i]];
    int c = 0;
    for (auto x : mp)
        mp[x.first] = ++c, V[c] = x.first;
    root[0] = t.build(1, n);
    map<int, int> last;
    for (int i = 1; i <= n; i++)
    {
        int val = mp[a[i]];
        if (last.count(val))
            root[i] = t.upd(root[i - 1], 1, n, last[val], 0);
        else
            root[i] = root[i - 1];
        root[i] = t.upd(root[i], 1, n, i, 1);
        last[val] = i;
    }
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << t.query(root[r], 1, n, l, r) << "\n";
    }
    return 0;
}