#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <cmath>
using namespace std;
 
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
 
/*
    * SOS DP pentru adunare pe submultimi
    * Descriere: Se aduna valorile pe fiecare submultime a unui vector de lungime 2^n.
    * Solutie: Se foloseste programarea dinamica pe submultimi (SOS DP) pentru a calcula suma pe fiecare submasca.
    * Complexitate: O(n * 2^n)
*/
void SOS_DP_add(vector<long long>& F) {
    int LEN = F.size();
    for (int ind = 0; ind < log2(LEN); ind++)
        for (int mask = 0; mask < LEN; mask++)
            if (mask & (1 << ind))
                F[mask] = F[mask] + F[mask ^ (1 << ind)];
}
 
/*
    * SPOJ_NGCD-NO_GCD 
    * Descriere: Se cere sa se calculeze numarul de perechi (i, j) astfel incat GCD(a[i], a[j]) = 1 sau p.
    * Solutie: Se foloseste programarea dinamica pe submultimi (SOS DP) pentru a calcula numarul de perechi coprime.
    * Complexitate: O(n * 2^P), unde P este numarul de numere prime considerate (15 in acest caz).
*/
long long NGCD(int n, const vector<long long>& a, const vector<int>& primes) {
    const int P = 15;
    int N = 1 << P;
    vector<int> mask(n + 1, 0);
    vector<long long> A(N, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < P; ++j) {
            if (a[i] % primes[j] == 0) {
                mask[i] |= (1 << j);
            }
        }
        A[mask[i]]++;
    }
    vector<long long> F = A;
    SOS_DP_add(F); 
    long long ans = 0, fullMask = N - 1;
    for (int i = 0; i < n; ++i) {
        int X = a[i], tilda_X = fullMask ^ mask[i];
        for (int b = 0; b < P; ++b) 
            if (mask[i] & (1 << b)) {
                ans += F[tilda_X | (1 << b)] - F[tilda_X]; // CNT2(mask)
            }
        ans += F[tilda_X]; // CNT1(mask)
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
 
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    
    long long result = NGCD(n, a, primes);
    cout << result << '\n';
}
 
int main() {
    fast
 
    int T;
    cin >> T;
    while (T--)
        solve();
 
    return 0; 
} 