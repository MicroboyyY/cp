#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;

struct PST
{
#define lc t[cur].l
#define rc t[cur].r
    struct node
    {
        int l = 0, r = 0, val = 0, lazy = 0;
    } t[40 * N];
    int T = 0;

    int build(int b, int e)
    {
        int cur = ++T;
        t[cur].l = t[cur].r = 0;
        t[cur].val = 0;
        t[cur].lazy = 0;
        if (b == e)
            return cur;
        int mid = (b + e) >> 1;
        t[cur].l = build(b, mid);
        t[cur].r = build(mid + 1, e);
        t[cur].val = t[t[cur].l].val + t[t[cur].r].val;
        return cur;
    }

    void push(int cur, int b, int e)
    {
        if (t[cur].lazy == 0 || b == e)
            return;
        int mid = (b + e) >> 1;
        int oldL = t[cur].l;
        int oldR = t[cur].r;

        int newL = ++T;
        t[newL] = t[oldL];
        t[newL].lazy += t[cur].lazy;
        t[newL].val += t[cur].lazy * (mid - b + 1);

        int newR = ++T;
        t[newR] = t[oldR];
        t[newR].lazy += t[cur].lazy;
        t[newR].val += t[cur].lazy * (e - mid);

        t[cur].l = newL;
        t[cur].r = newR;
        t[cur].lazy = 0;
    }

    int upd(int pre, int b, int e, int l, int r, int v)
    {
        if (b > r || e < l)
            return pre;
        int cur = ++T;
        t[cur] = t[pre];
        if (b >= l && e <= r)
        {
            t[cur].lazy += v;
            t[cur].val += v * (e - b + 1);
            return cur;
        }
        push(cur, b, e);
        int mid = (b + e) >> 1;
        int L = upd(t[cur].l, b, mid, l, r, v);
        int R = upd(t[cur].r, mid + 1, e, l, r, v);
        t[cur].l = L;
        t[cur].r = R;
        t[cur].val = t[L].val + t[R].val;
        return cur;
    }

    int query(int cur, int b, int e, int l, int r, int add = 0)
    {
        if (!cur || b > r || e < l)
            return 0;
        if (b >= l && e <= r)
            return t[cur].val + add * (e - b + 1);
        int mid = (b + e) >> 1;
        int nadd = add + t[cur].lazy;
        return query(t[cur].l, b, mid, l, r, nadd) +
               query(t[cur].r, mid + 1, e, l, r, nadd);
    }
} t;

int root[N], a[N];

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    root[0] = t.build(1, n);

    return 0;
}
