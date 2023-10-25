#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 10;
#define endl '\n'
#define all(x) sort((x).begin(), (x).end())
#define f(i, n) for (int i = 0; i < n; i++)

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 13;
    vector<int> v{12, 5, 10, 1}, v2 = {15, 5, 7, 15, 31}, cnt(34);
    int s = 0;
    // f(i, 4)
    // {
    //     f(j, 5) s += (v[i] & v2[j]);
    // }
    // f(i, 4) s += (v[i] & n);
    // cout << s << endl;
    f(i, 5) // convert O(N2)->O(32n);
    {
        f(j, 31)
        {
            cnt[j] += (v2[i] >> j) & 1;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 31; j++)
        {
            if ((v[i] >> j) & 1)
            {
                s += (1ll << j) * cnt[j];
            }
        }
    }
    // f(i, 31)
    // {
    //     if ((n >> i) & 1)
    //     {
    //         s += (1ll << i) * cnt[i];
    //     }
    // }
    cout << s << '\n';

    return 0;
}