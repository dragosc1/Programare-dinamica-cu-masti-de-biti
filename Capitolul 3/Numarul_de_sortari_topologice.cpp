#include <bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

const int MOD = 998244353;

/*
    * Problema: Numarul de sortari topologice
    * Descriere: Se cere sa se calculeze numarul de sortari topologice ale unui graf orientat aciclic (DAG).
    * Solutie: Se foloseste programarea dinamica pe submultimi pentru a calcula numarul de sortari topologice.
    * Complexitate: O(2^n * n)
*/
int countTopologicalSorts(int n, const vector<pair<int, int>>& edges) {
    vector<int> dependenta(n, 0), dp(1 << n, 0);
    for (auto [x, y] : edges) dependenta[y] |= (1 << x);
    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0 && (mask & dependenta[i]) == dependenta[i]) {
                dp[mask | (1 << i)] = (dp[mask | (1 << i)] + dp[mask]) % MOD;
            }
        }
    }
    return dp[(1 << n) - 1];
}

void solve() {
    // Citirea numărului de noduri și a muchiilor
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, int>> edges;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--; // convertire la indexare 0
        edges.emplace_back(x, y);
    }

    // Calcularea numărului de sortări topologice
    int result = countTopologicalSorts(n, edges);
    cout << result << '\n';
}
int main() {
    fast
    solve();
    return 0;
}

