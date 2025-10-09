#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 4e5 + 9;

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

long long ans[N];
// duita string er moddeh koyta index a value same oitah precomp kore rakheh then first paibo query te
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s, t;
    cin >> s >> t;
    vector<int> ans(s.size() - t.size() + 1, 0);
    for (auto c : {'A', 'C', 'G', 'T'})
    {
        vector<int> a, b;
        for (auto x : s)
            a.push_back((x == c));
        for (auto x : t)
            b.push_back((x == c));
        int n = a.size(), m = b.size();
        reverse(b.begin(), b.end());
        auto v = multiply(a, b);
        for (int i = 0; i < n - m + 1; i++)
            ans[i] += v[i + m - 1];
    }
    int mx = 0;
    for (auto x : ans)
        mx = max(mx, x);
    cout << t.size() - mx << "\n";
    return 0;
}