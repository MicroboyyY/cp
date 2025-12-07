#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;

struct SegTree
{
#define lc t[cur].l
#define rc t[cur].r
    struct node
    {
        int l = 0, r = 0;
        int val = 0;
        int lazy = 0;
    } t[4 * N];
    int T = 0;

    void build(int cur, int b, int e, int a[])
    {
        if (b == e)
        {
            t[cur].val = a[b];
            return;
        }
        int mid = (b + e) >> 1;
        lc = cur << 1;
        rc = cur << 1 | 1;
        build(lc, b, mid, a);
        build(rc, mid + 1, e, a);
        t[cur].val = t[lc].val + t[rc].val;
    }

    void push(int cur, int b, int e)
    {
        if (t[cur].lazy == 0)
            return;
        t[cur].val += (e - b + 1) * t[cur].lazy;
        if (b != e)
        {
            lc = cur << 1;
            rc = cur << 1 | 1;
            t[lc].lazy += t[cur].lazy;
            t[rc].lazy += t[cur].lazy;
        }
        t[cur].lazy = 0;
    }

    void upd(int cur, int b, int e, int l, int r, int v)
    {
        push(cur, b, e);
        if (b > r || e < l)
            return;
        if (b >= l && e <= r)
        {
            t[cur].lazy += v;
            push(cur, b, e);
            return;
        }
        int mid = (b + e) >> 1;
        lc = cur << 1;
        rc = cur << 1 | 1;
        upd(lc, b, mid, l, r, v);
        upd(rc, mid + 1, e, l, r, v);
        t[cur].val = t[lc].val + t[rc].val;
    }

    int query(int cur, int b, int e, int l, int r)
    {
        push(cur, b, e);
        if (b > r || e < l)
            return 0;
        if (b >= l && e <= r)
            return t[cur].val;
        int mid = (b + e) >> 1;
        lc = cur << 1;
        rc = cur << 1 | 1;
        return query(lc, b, mid, l, r) + query(rc, mid + 1, e, l, r);
    }
} st;

int a[N];

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    st.build(1, 1, n, a);

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r, v;
            cin >> l >> r >> v;
            st.upd(1, 1, n, l, r, v);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << st.query(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}
