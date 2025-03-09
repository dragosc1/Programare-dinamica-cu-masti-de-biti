#include <bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

// primele numere prime pana in 72, primes[0] = 2, primes[1] = 3, primes[2] = 5, ...
int primes[20];

// e[i] = 1 daca i este numar prim, e[i] = 0 altfel
bool e[73];

// L = numarul de numere prime pana in 72
int L = 0;

// precalculeaza primele numere prime pana in 72
void pre() {
    for (int i = 2; i <= 72; i++)
        if (!e[i]) {
            primes[L++] = i;
            for (int j = i * i; j <= 72; j += i)
                e[j] = 1;
        }
}

// dp[i] = numarul de submultimi care contin numerele de la A la B si sunt coprime intre ele, avand ca si factori primi numerele prime din masca de biti mask
long long dp[(1 << 20)];

int main() {
    pre();
    // citire date de intrare
    long long A, B;
    cin >> A >> B;

    // dp[0] = 1 deoarece multimea vida este coprima cu orice numar
    dp[0] = 1;

    // pentru fiecare numar de la A la B
    for (long long i = A; i <= B; i++) {
        // now_mask = masca de biti care retine daca numarul i este divizibil cu un numar prim pana in 72
        int now_mask = 0;
        for (int j = 0; j < L; j++) 
            if (i % primes[j] == 0)
                now_mask |= (1 << j);

        // pentru fiecare masca de biti
        for (int mask = (1 << L) - 1; mask >= 0; mask--)
            if ((mask & now_mask) == 0) // noua masca de biti nu are factori primi in comun cu masca de biti mask
                dp[mask | now_mask] += dp[mask];
    }

    // S = numarul de submultimi care contin numerele de la A la B si sunt coprime cu toate numerele prime pana in 72
    long long S = 0;
    for (int i = 0; i < (1 << L); i++)
        S += dp[i];

    // afisare rezultat
    cout << S << '\n';
    return 0;
}