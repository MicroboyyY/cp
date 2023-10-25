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
#define endl '\n'
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> v(n + 1), psa(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
        psa[i] = psa[i - 1] + v[i];
        psa[i] = ((psa[i] % n) + n) % n;
    }
    // for (auto x : psa)
    //     cout << x << ' ';
    map<ll, ll> m;
    m[0] = 1;
    ll s = 0;
    for (int i = 1; i <= n; i++)
    {
        int extra = ((psa[i] % n) + n) % n;
        s += m[extra];
        m[extra]++;
    }
    cout << s << '\n';

    return 0;
}