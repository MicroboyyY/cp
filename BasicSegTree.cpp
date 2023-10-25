#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "algo/debug.h"
// #define cerr cout
#else
#define deb(...) 122
#endif
#define ll long long
const int N = 1e5 + 10;
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
const int n = 5;
int t[n * 4];
void build(int node, int b, int e, vector<int> &v) // logN
{
    if (b == e)
    {
        t[node] = v[b];
        return;
    }
    int mid = (b + e) >> 1;
    int l = 2 * node, r = 2 * node + 1;
    build(l, b, mid, v);
    build(r, mid + 1, e, v);
    t[node] = t[l] + t[r];
}
int query(int node, int b, int e, vector<int> &v, int i, int j) // logN
{
    if (e < i || b > j)
    {
        return 0;
    }
    if (i <= b && j >= e)
        return t[node];
    int mid = (b + e) / 2;
    int l = 2 * node, r = 2 * node + 1;
    return query(l, b, mid, v, i, j) + query(r, mid + 1, e, v, i, j);
}
void upd(int node, int b, int e, vector<int> &v, int i, int x)
{
    if (b > i || e < i)
        return;
    if (b == e && e == i)
    {
        t[node] = x;
        return;
    }
    int l = 2 * node, r = 2 * node + 1;
    int mid = (b + e) / 2;
    upd(l, b, mid, v, i, x);
    upd(r, mid + 1, e, v, i, x);
    t[node] = t[l] + t[r];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> v(8);
    f(i, n) v[i + 1] = i + 1;
    build(1, 1, 5, v);
    // v[6] = 7; // 1 2 3 4 5
    // build(1, 1, 5, v);
    // cout<<t[1]<<'\n';
    cout << query(1, 1, 5, v, 2, 4);
    // 1 2 10 4 5
    upd(1, 1, 5, v, 3, 10);
    cout << endl;
    cout << query(1, 1, 5, v, 2, 4);
    return 0;
}