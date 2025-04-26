#include <bits/stdc++.h>
using namespace std;

int main() {
    // Citire date de intrare
    int n;
    cin >> n;
    vector<int> A(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        cin >> A[i];
    }
    
    vector<int> dp(1 << n);
    // Initializare dp
    dp = A; // dp[mask][-1] = A[mask]
     
    // Calculare suma pe fiecare submasca - Varianta eficienta ca timp de memorie
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << i)) {
                // dp[mask][i] += dp[mask ^ (1 << i)][i - 1]
                dp[mask] += dp[mask ^ (1 << i)];
            }
            

    // Afisare rezultat
    for (int mask = 0; mask < (1 << n); mask++) {
        cout << "Suma pe submasca " << mask << ": " << dp[mask] << '\n';
    }
    return 0;
}