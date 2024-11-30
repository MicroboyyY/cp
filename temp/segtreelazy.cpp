#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
const int N = 100007;
#define int long long
int arr[N];
ll t[4 * N], lazy[4 * N];
ll marge(int l, int r)
{
    return min(t[l], t[r]);
}
void push(int n, int b, int e)
{
    if (lazy[n] == 0)
        return;
    t[n] = t[n] + lazy[n];
    if (b != e)
    {
        int mid = (b + e) / 2, l = 2 * n, r = l + 1;
        lazy[l] += lazy[n];
        lazy[r] += lazy[n];
    }
    lazy[n] = 0;
}
void build(int n, int b, int e)
{
    lazy[n] = 0;
    if (b == e)
    {
        t[n] = arr[b];
        return;
    }
    int mid = (b + e) / 2, l = 2 * n, r = l + 1;
    build(l, b, mid), build(r, mid + 1, e);
    t[n] = marge(l, r);
}
void upd(int n, int b, int e, int i, int j, int v)
{
    push(n, b, e);
    if (e < i or b > j)
        return;
    if (i <= b and j >= e)
    {
        lazy[n] = v;
        push(n, b, e);
        return;
    }
    int mid = (b + e) / 2, l = 2 * n, r = l + 1;
    upd(l, b, mid, i, j, v), upd(r, mid + 1, e, i, j, v);
    t[n] = marge(l, r);
}
ll query(int n, int b, int e, int i, int j)
{
    push(n, b, e);
    if (e < i or b > j)
        return INT_MAX;
    if (i <= b and j >= e)
    {
        return t[n];
    }
    int mid = (b + e) / 2, l = 2 * n, r = l + 1;
    return min(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    build(1, 1, n);
    while (q--)
    {
        int ty;
        cin >> ty;
        if (ty == 1)
        {
            int l, r, v;
            cin >> l >> r >> v;
            l++;
            upd(1, 1, n, l, r, v);
        }
        else
        {
            int i, j;
            cin >> i >> j;
            i++;
            cout << query(1, 1, n, i, j) << '\n';
        }
    }
}