#include <bits/stdc++.h>
using namespace std;
// #define int long long

const double PI = acos(-1);
struct base
{
    double a, b;
    base(double a = 0, double b = 0) : a(a), b(b) {}
    const base operator+(const base &c) const
    {
        return base(a + c.a, b + c.b);
    }
    const base operator-(const base &c) const
    {
        return base(a - c.a, b - c.b);
    }
    const base operator*(const base &c) const
    {
        return base(a * c.a - b * c.b, a * c.b + b * c.a);
    }
};
void fft(vector<base> &p, bool inv = 0)
{
    int n = p.size(), i = 0;
    for (int j = 1; j < n - 1; ++j)
    {
        for (int k = n >> 1; k > (i ^= k); k >>= 1)
            ;
        if (j < i)
            swap(p[i], p[j]);
    }
    for (int l = 1, m; (m = l << 1) <= n; l <<= 1)
    {
        double ang = 2 * PI / m;
        base wn = base(cos(ang), (inv ? 1. : -1.) * sin(ang)), w;
        for (int i = 0, j, k; i < n; i += m)
        {
            for (w = base(1, 0), j = i, k = i + l; j < k; ++j, w = w * wn)
            {
                base t = w * p[j + l];
                p[j + l] = p[j] - t;
                p[j] = p[j] + t;
            }
        }
    }
    if (inv)
        for (int i = 0; i < n; ++i)
            p[i].a /= n, p[i].b /= n;
}
vector<long long> multiply(vector<int> &a, vector<int> &b)
{
    int n = a.size(), m = b.size(), t = n + m - 1, sz = 1;
    while (sz < t)
        sz <<= 1;
    vector<base> x(sz), y(sz), z(sz);
    for (int i = 0; i < sz; ++i)
    {
        x[i] = i < (int)a.size() ? base(a[i], 0) : base(0, 0);
        y[i] = i < (int)b.size() ? base(b[i], 0) : base(0, 0);
    }
    fft(x), fft(y);
    for (int i = 0; i < sz; ++i)
        z[i] = x[i] * y[i];
    fft(z, 1);
    vector<long long> ret(sz);
    for (int i = 0; i < sz; ++i)
        ret[i] = (long long)round(z[i].a);
    while ((int)ret.size() > 1 && ret.back() == 0)
        ret.pop_back();
    return ret;
}

const int N = 2e5 + 9;

vector<int> g[N], ng[N];
int sz[N], n, k1, k2;
long long cnt[N], ans;
int tot, done[N], cenpar[N], vis[N], mx;
void calc_sz(int u, int p)
{
    tot++;
    sz[u] = 1;
    for (auto v : g[u])
    {
        if (v == p || done[v])
            continue;
        calc_sz(v, u);
        sz[u] += sz[v];
    }
}
int find_cen(int u, int p)
{
    for (auto v : g[u])
    {
        if (v == p || done[v])
            continue;
        else if (sz[v] > tot / 2)
            return find_cen(v, u);
    }
    return u;
}

void add(int u, int p, int d, vector<int> &dep)
{
    dep.push_back(d);
    for (auto v : g[u])
    {
        if (v == p || done[v])
            continue;
        add(v, u, d + 1, dep);
    }
}

void decompose(int u, int pre)
{
    tot = 0;
    calc_sz(u, pre);
    int cen = find_cen(u, pre);
    cenpar[cen] = pre;
    done[cen] = 1;
    cnt[0] = 1;
    mx = 0;
    vector<int> use, v;
    use.push_back(0);
    for (auto v : g[cen])
    {
        if (done[v])
            continue;
        vector<int> dep;
        add(v, cen, 1, dep);
        vector<int> c2(*max_element(dep.begin(), dep.end()) + 1, 0);
        for (auto d : dep)
            c2[d]++;
        auto c = multiply(c2, c2);
        for (int i = k1; i <= k2 and i < (int)c.size(); i++)
            ans -= c[i];
        for (auto d : dep)
        {
            if (d > mx)
                mx = d;
            use.push_back(d);
        }
    }
    vector<int> new_cnt(*max_element(use.begin(), use.end()) + 1, 0);
    for (auto d : use)
        new_cnt[d]++;
    auto c = multiply(new_cnt, new_cnt);
    for (int i = k1; i <= k2 and i < (int)c.size(); i++)
        ans += c[i];
    use.clear();
    for (auto v : g[cen])
    {
        if (!done[v])
            decompose(v, cen);
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k1 >> k2;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    decompose(1, 0);
    cout << ans / 2 << '\n';

    return 0;
}