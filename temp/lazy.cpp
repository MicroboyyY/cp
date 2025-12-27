#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
const int N = 3e5 + 9;
const int LG = 22;
struct ST
{
#define lc (n << 1)
#define rc ((n << 1) + 1)
    long long t[4 * N], lazyadd[4 * N], lazyset[4 * N];
    ST()
    {
        memset(t, 0, sizeof t);
        memset(lazyset, -1, sizeof lazyset);
        memset(lazyadd, 0, sizeof lazyadd);
    }
    inline void push(int n, int b, int e)
    { // change this
        if (lazyset[n] != -1)
        {
            t[n] = lazyset[n] * (e - b + 1);
            if (b != e)
            {
                lazyset[lc] = lazyset[n];
                lazyset[rc] = lazyset[n];
                lazyadd[lc] = 0;
                lazyadd[rc] = 0;
            }
            lazyset[n] = -1;
        }
        if (lazyadd[n] != 0)
        {
            t[n] += lazyadd[n] * (e - b + 1);
            if (b != e)
            {
                lazyadd[lc] += lazyadd[n];
                lazyadd[rc] += lazyadd[n];
            }
            lazyadd[n] = 0;
        }
    }
    inline long long combine(long long a, long long b)
    { // change this
        return a + b;
    }
    inline void pull(int n)
    { // change this
        t[n] = t[lc] + t[rc];
    }
    void build(int n, int b, int e)
    {
        lazyset[n] = -1; // change this
        lazyadd[n] = 0;
        if (b == e)
        {
            t[n] = 0;
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        pull(n);
    }
    void updset(int n, int b, int e, int i, int j, long long v)
    {
        push(n, b, e);
        if (j < b || e < i)
            return;
        if (i <= b && e <= j)
        {
            lazyset[n] = v; // set lazyset
            lazyadd[n] = 0;
            push(n, b, e);
            return;
        }
        int mid = (b + e) >> 1;
        updset(lc, b, mid, i, j, v);
        updset(rc, mid + 1, e, i, j, v);
        pull(n);
    }
    void updadd(int n, int b, int e, int i, int j, long long v)
    {
        push(n, b, e);
        if (j < b || e < i)
            return;
        if (i <= b && e <= j)
        {
            lazyadd[n] += v; // set lazyset
            push(n, b, e);
            return;
        }
        int mid = (b + e) >> 1;
        updadd(lc, b, mid, i, j, v);
        updadd(rc, mid + 1, e, i, j, v);
        pull(n);
    }
    long long query(int n, int b, int e, int i, int j)
    {
        push(n, b, e);
        if (i > e || b > j)
            return 0; // return null
        if (i <= b && e <= j)
            return t[n];
        int mid = (b + e) >> 1;
        return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }
} tr;
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}