#include <bits/stdc++.h>
using namespace std;
 
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
 
const int MOD = 1e9 + 7;
 
/*
    * Problema cacului de supramasti 
    * Descriere: Se cere sa se calculeze suma elementelor pentru fiecare supramasca a unui vector de lungime 2^n, folosind programarea dinamica pe submultimi.
    * Solutie: Se foloseste SOS DP pentru a calcula suma pe fiecare supramasca.
    * Complexitate: O(n * 2^n)
    * Operator +
*/ 
void SOS_DP_prime_add(vector<int>& F) {
    int LEN = F.size();
    for (int ind = 0; ind < log2(LEN); ind++)
        for (int mask = LEN - 1; mask >= 0; mask--)
            if (!(mask & (1 << ind)))
                F[mask] = (F[mask] + F[mask ^ (1 << ind)]) % MOD;
}

/*
    * Problema cacului de supramasti 
    * Descriere: Se cere sa se calculeze suma elementelor pentru fiecare supramasca a unui vector de lungime 2^n, folosind programarea dinamica pe submultimi.
    * Solutie: Se foloseste SOS DP pentru a calcula suma pe fiecare supramasca.
    * Complexitate: O(n * 2^n)
    * Operator -
*/ 
void SOS_DP_prime_sub(vector<int>& F) {
    int LEN = F.size();
    for (int ind = 0; ind < log2(LEN); ind++)
        for (int mask = LEN - 1; mask >= 0; mask--)
            if (!(mask & (1 << ind)))
                F[mask] = (1LL * F[mask] - F[mask ^ (1 << ind)] + MOD) % MOD;
}

/*
    * Functie pentru calcularea puterii modulo MOD
    * @param base: baza
    * @param exp: exponentul
    * @param MOD: modulul
    * @return: baza^exp % MOD
*/
int pow_mod(int base, int exp, int MOD) {
    int result = 1;
    base = base % MOD;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (1LL * result * base) % MOD;
        }
        exp = exp >> 1;
        base = (1LL * base * base) % MOD;
    }
    return result;
}

/*
    * Functie pentru calcularea numarului de submultimi care au AND-ul egal cu X
    * @param A: vectorul de intrare
    * @param LEN: lungimea vectorului (2^n)
    * @return: vectorul cu numarul de submultimi pentru fiecare AND
*/
vector<int> AndSubsetCount(const vector<int>& A, int LEN) {
    vector<int> F_prime(LEN, 0);
    for (int x : A) {
        F_prime[x]++;
    }
    SOS_DP_prime_add(F_prime);
    for (int X = 0; X < LEN; ++X) {
        F_prime[X] = (1LL * pow_mod(2, F_prime[X], MOD) - 1 + MOD) % MOD;
    }
    SOS_DP_prime_sub(F_prime); 
    return F_prime;
}

void solve() {
    // Citire date de intrare
    int n;
    cin >> n;
 
    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];
 
    int max_val = *max_element(A.begin(), A.end());
    int MAX_BITS = (int)ceil(log2(max_val + 1));
    int LEN = 1 << MAX_BITS;

    vector<int> F = AndSubsetCount(A, LEN);

    // Afisare rezultat
    for (int i = 0; i <= n; i++)
        cout << F[i] << ' ';
}   
 
int main() {
    fast
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0; 
}