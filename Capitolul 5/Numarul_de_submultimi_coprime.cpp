#include <bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

// primele numere prime pana in 72, primes[0] = 2, primes[1] = 3, primes[2] = 5, ...
vector<int> primes;

// e[i] = 1 daca i este numar prim, e[i] = 0 altfel
bool e[73];

// L = numarul de numere prime pana in 72
int L = 0;

// precalculeaza primele numere prime pana in 72
void pre() {
    for (int i = 2; i <= 72; i++)
        if (!e[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= 72; j += i)
                e[j] = 1;
        }
}

/*
    * Functie pentru calcularea numarului de submultimi coprime
    * @param A: limita inferioara
    * @param B: limita superioara
    * @param primesList: lista de numere prime
    * @return: numarul de submultimi coprime in intervalul [A, B]
*/
long long calculateDp(long long A, long long B, const vector<int>& primesList) {
    const int m = primesList.size();
    vector<long long> dp(1 << m, 0LL);
    dp[0] = 1;

    for (long long i = A; i <= B; i++) {
        int nowMask = 0;
        for (int j = 0; j < m; j++) {
            if (i % primesList[j] == 0)
                nowMask |= (1 << j);
        }
        for (int mask = (1 << m) - 1; mask >= 0; mask--) {
            if ((mask & nowMask) == 0)
                dp[mask | nowMask] += dp[mask];
        }
    }
    
    return accumulate(dp.begin(), dp.end(), 0LL);
}

int main() {
    pre();
    // citire date de intrare
    long long A, B;
    cin >> A >> B;

    int S = calculateDp(A, B, primes);
    // afisare rezultat
    cout << S << '\n';
    return 0;
}