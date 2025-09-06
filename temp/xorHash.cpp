#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (int i = 0; i < n; i++)
#define trace(x) cerr << #x << ": " << x << '\n'
#define int ll
int rnd()
{
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<long long> dist(0, 1e18);
    return dist(rng);
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tt;
    cin >> tt;
    while (tt--)
    {
        int n, q;
        cin >> n >> q;
        vector<int> a(n + 1);
        vector<pair<int, int>> pref(n + 1);
        pref[0] = {0, 0};
        set<int> st;
        map<int, pair<int, int>> mp;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            if (!st.count(a[i]))
            {
                st.insert(a[i]);
                mp[a[i]].first = rnd();
                mp[a[i]].second = rnd();
            }
            pref[i].first = pref[i - 1].first ^ mp[a[i]].first;
            pref[i].second = pref[i - 1].second ^ mp[a[i]].second;
        }
        while (q--)
        {
            int l, r;
            cin >> l >> r;
            if (pref[r] == pref[l - 1])
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }

    return 0;
}