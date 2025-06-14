/*
    Autor: Ciobanu Dragoș
*/
#include <bits/stdc++.h>
using namespace std;
 
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
 
int dp[2][(1 << 20)];
 
const int MOD = 1e9 + 7;
 
int main() {
    fast
    // citire date de intrare
    int n, m;
    cin >> n >> m;
    
    // Numarul de griduri gradient
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int mask = 0; mask < (1 << m); mask++) {
                if (!(mask & (1 << j))) {
                    dp[1][mask] = (dp[1][mask] + dp[0][mask]) % MOD;
                }
                if (!(mask & (1 << j)) && (j == 0 || !(mask & (1 << (j - 1))))) {
                    int new_mask = mask ^ (1 << j);
                    dp[1][new_mask] = (dp[1][new_mask] + dp[0][mask]) % MOD;
                }
                if (mask & (1 << j)) {
                    int new_mask = mask ^ (1 << j);
                    dp[1][new_mask] = (dp[1][new_mask] + dp[0][mask]) % MOD;
                }
            }
            for (int mask = 0; mask < (1 << m); mask++) {
                dp[0][mask] = dp[1][mask];
                dp[1][mask] = 0;
            }
        }
    }

    int result = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        result = (result + dp[0][mask]) % MOD;
    }

    // afisarea rezultatului
    result = result * 2 % MOD; // prima celula poate fi numar par sau impar
    cout << result << endl;
    return 0;
}