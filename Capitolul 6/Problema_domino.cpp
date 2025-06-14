/*
    Autor: Ciobanu Dragoș
*/
#include <bits/stdc++.h>
using namespace std;
 
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
 
int dp[2][(1 << 10)];
 
const int MOD = 1e9 + 7;
 
int main() {
    fast
    // citire date de intrare
    int N, M;
    cin >> N >> M;
    swap(N, M);

    // dp[0][k] = numarul de moduri de a plasa domino-uri pe o tabla de dimensiune n x m
    dp[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < (1 << M); k++) {
                dp[1][k ^ (1 << j)] = (dp[1][k ^ (1 << j)] + dp[0][k]) % MOD;
                if (j != M - 1 && !(k & (1 << j)) && !(k & (1 << (j + 1)))) {
                    dp[1][k ^ (1 << (j + 1))] =
                        (dp[1][k ^ (1 << (j + 1))] + dp[0][k]) % MOD;
                }
            }
            for (int k = 0; k < (1 << M); k++) 
                dp[0][k] = dp[1][k], dp[1][k] = 0;
        }
    }

    // afisarea rezultatului
    int rezultat = dp[0][0];
    cout << rezultat << '\n';
    return 0;
}