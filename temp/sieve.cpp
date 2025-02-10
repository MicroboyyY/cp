#include <bits/stdc++.h>
using namespace std;

const int N = 1e8 + 9;
bitset<N> f;
int spf[N];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n = N - 9;
    vector<int> primes;
    for (int i = 1; i < N; i++)
        spf[i] = i;
    for (int i = 2; i < N; i++)
    {
        for (int j = i; j < N; j += i)
        {
            spf[j] = min(spf[j], i);
        }
    }
    f[1] = true;
    for (int i = 2; i * i <= n; i++)
    {
        if (!f[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                f[j] = true;
            }
        }
    }
    for (int i = 2; i <= n; i++)
    {
        if (!f[i])
        {
            primes.push_back(i);
        }
    }
    cout << primes.size() << '\n';
    return 0;
}