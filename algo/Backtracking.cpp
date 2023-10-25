#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back
#define vll vector<ll>
#define f(i, n) for (int i = 0; i < n; i++)
vector<vector<ll>> subs;
vector<ll> temp;
void fun(vector<ll> v, ll i, ll n)
{
    if (i == n)
    {
        subs.pb(temp);
        return;
    }
    temp.pb(v[i]);
    fun(v, i + 1, n);
    temp.pop_back();
    fun(v, i + 1, n);
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vll v(n);
    f(i, n) cin >> v[i];
    fun(v, 0, n);
    // cout<<subs.size();
    for (auto x : subs)
    {
        for (auto d : x)
        {
            cout << d << ' ';
        }
        cout << '\n';
    }

    return 0;
}
