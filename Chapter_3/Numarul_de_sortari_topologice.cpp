#include <bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
// Soluțiile pot fi foarte multe și astfel se folosește un MOD corespunzător
const int MOD = 998244353;
// dependenta[i] = nodurile adiacenta lui i sub forma de mască de biți
int dependenta[19];
// dp[i] = numărul de sortari topologice care cuprinde nodurile din masca de biți i
int dp[1 << 19];
void solve() {
    int n, m;
    // n = numărul de noduri, m = numărul de muchii
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        // citire muchii graf orientat aciclic
        int x, y;
        cin >> x >> y;
        // Nodurile vor fi indexate de la 0
        x--;
        y--;
        // adaugare dependenta nod x
        dependenta[y] |= (1 << x);
    }
    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            // nodul i nu se află în mască și nodul i are gradul interior 0 în mască
            if ((mask & (1 << i)) == 0 && (mask & dependenta[i]) == dependenta[i]) {
                // adaugare sortari topologice 
                dp[mask | (1 << i)] = (dp[mask | (1 << i)] + dp[mask]) % MOD;
            }
        }
    }
    // afișare rezultat
    cout << dp[(1 << n) - 1] << '\n';
}
int main() {
    fast
    solve();
    return 0;
}

