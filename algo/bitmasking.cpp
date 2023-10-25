#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back
#define vi vector<int>
#define vll vector<ll>
#define mp make_pair
#define pq priority_queue<int>
#define pi pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define PI acos(-1)
const int M = 1e9 + 7;
ll binExp(ll a, ll b)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a;
        a *= a;
        b /= 2;
    }
    return res;
}
ll gcd(ll a, ll b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
ll lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}
void solve()
{
    int n;
    cin >> n;
    vll v(n);
    f(i, n) cin >> v[i];
    vector<vector<ll>> ans;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        vector<ll> temp;
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                temp.push_back(v[i]);
            }
        }
        ans.pb(temp);
    }
    for (auto x : ans)
    {
        for (auto d : x)
        {
            cout << d << ' ';
        }
        cout << endl;
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    // cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}