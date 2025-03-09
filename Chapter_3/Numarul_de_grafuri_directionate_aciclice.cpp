#include <bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
// Soluțiile pot fi foarte multe și astfel se folosește un MOD corespunzător
const int MOD = 998244353;
// dependentă[i] = mască de biți cu toate nodurile care ies din nodul i. 
int dependenta[19];
// dp[mask] = numărul de grafuri orientate aciclice cu nodurile din masca mask.
int dp[1 << 19];
// independent[mask] = flag pentru masca de biți mask care este egal cu true dacă toate // nodurile din mask sunt independente unul față de celălalt (nu sunt muchii între ele).
int independent[1 << 19];
// semn[mask] = 1 dacă masca de biți mask conține un număr impar de noduri și -1 
int semn[1 << 19];
void solve() {
   // n = numărul de noduri, m = numărul de muchii
   int n, m;
   cin >> n >> m;
   for (int i = 1; i <= m; i++) {
       int x, y;
       cin >> x >> y;
       x--;
       y--;
       dependenta[x] |= (1 << y);
       dependenta[y] |= (1 << x);
   }
   independent[0] = 1;
   for (int i = 0; i < (1 << n); i++) {
       // ultimul bit sub forma de (1 << bit)
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
   // calculare dp[mask] folosind PIE
   dp[0] = 1;
   for (int i = 1; i < (1 << n); i++) {
       for (int j = i; j; j = (j - 1) & i)
           if (independent[j]) {
               dp[i] = (1LL * dp[i] + 1LL * dp[i ^ j] * semn[j] % MOD + MOD) % MOD;
           }
   }
   // rezultat număr de DAG-uri posibile
   cout << 1LL * dp[(1 << n) - 1] << '\n';
}
int main() {
   fast
   solve();
   return 0;
}

