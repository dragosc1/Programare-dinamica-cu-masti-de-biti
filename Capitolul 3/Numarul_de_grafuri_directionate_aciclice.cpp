/*
    Autor: Ciobanu Dragoș
*/
#include <bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

const int MOD = 998244353;

/*
    * Problema: Numarul de grafuri orientate aciclice (DAG)
    * Descriere: Se cere sa se calculeze numarul de grafuri orientate aciclice (DAG) cu un anumit numar de noduri si muchii.
    * Solutie: Se foloseste programarea dinamica pe submultimi pentru a calcula numarul de DAG-uri.
    * Complexitate: O(3^n)
*/
int countDAGs(int n, const vector<pair<int, int>>& edges) {
    vector<int> dependenta(n, 0), dp(1 << n, 0), independent(1 << n, 0), semn(1 << n, 0);
    for (auto [x, y] : edges) {
        dependenta[x] |= (1 << y);
        dependenta[y] |= (1 << x);
    }
    independent[0] = 1;
    for (int i = 0; i < (1 << n); i++) {
        int ultimul_bit = i & ~(i - 1);
        int ultima_masca = i ^ ultimul_bit;
        if (independent[ultima_masca] && ((ultima_masca & dependenta[__builtin_ctz(ultimul_bit)]) == 0))
            independent[i] = 1;
    }
    semn[0] = -1;
    for (int i = 1; i < (1 << n); i++) {
        int ultimul_bit = i & ~(i - 1);
        semn[i] = semn[i ^ ultimul_bit] * -1;
    }
    dp[0] = 1;
    for (int i = 1; i < (1 << n); i++) {
        for (int j = i; j; j = (j - 1) & i)
            if (independent[j]) {
                dp[i] = (1LL * dp[i] + 1LL * dp[i ^ j] * semn[j] % MOD + MOD) % MOD;
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
        x--; y--;
        edges.emplace_back(x, y);
    }

    // Calcularea numărului de grafuri orientate aciclice
    int result = countDAGs(n, edges);
    cout << result << '\n';
}
int main() {
   fast
   solve();
   return 0;
}

