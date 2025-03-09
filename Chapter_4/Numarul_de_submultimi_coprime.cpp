#include <bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define int long long

int primes[101];
bool e[101];
int L = 0;

void pre() {
    for (int i = 2; i <= 72; i++)
        if (!e[i]) {
            primes[L++] = i;
            for (int j = i * i; j <= 72; j += i)
                e[j] = 1;
        }
}

int dp[(1 << 20)];

int32_t main() {
    pre();
    int A, B;
    cin >> A >> B;
    dp[0] = 1;
    for (int i = A; i <= B; i++) {
        int now_mask = 0;
        for (int j = 0; j < L; j++) 
            if (i % primes[j] == 0)
                now_mask |= (1 << j);
        for (int mask = (1 << L) - 1; mask >= 0; mask--)
            if ((mask & now_mask) == 0)
                dp[mask | now_mask] += dp[mask];
    }
    int S = 0;
    for (int i = 0; i < (1 << L); i++)
        S += dp[i];
    cout << S << '\n';
    return 0;
}