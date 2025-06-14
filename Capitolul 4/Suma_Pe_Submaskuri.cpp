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
    
    // Calculare suma pe fiecare submasca - Varianta eficienta ca timp de memorie
    vector<int> F(1 << n);
    F = A; 
    for (int ind = 0; ind < n; ind++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << ind)) {
                F[mask] += F[mask ^ (1 << ind)];
            }
            
    // Afisare rezultat
    for (int mask = 0; mask < (1 << n); mask++) {
        cout << "Suma pe submasca " << mask << ": " << F[mask] << '\n';
    }
    return 0;
}