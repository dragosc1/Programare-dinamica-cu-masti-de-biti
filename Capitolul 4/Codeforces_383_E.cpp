/*
    Autor: Ciobanu Dragoș
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <cmath>
using namespace std;
 
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
 
/*
    * Problema: Suma pe submasca
    * Descriere: Se cere sa se calculeze suma elementelor pentru fiecare submasca a unui vector de lungime 2^n.
    * Solutie: Se foloseste programarea dinamica pe submultimi pentru a calcula suma pe fiecare submasca.
    * Complexitate: O(n * 2^n)
*/
void SOS_DP_add(vector<int>& F) {
    int LEN = F.size();
    for (int ind = 0; ind < log2(LEN); ind++)
        for (int mask = 0; mask < LEN; mask++)
            if (mask & (1 << ind))
                F[mask] = F[mask] + F[mask ^ (1 << ind)];
}

int main() {
    fast
    // citire date de intrare
    int n;
    cin >> n;
    vector<int> A(1 << 24), F(1 << 24);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int now = accumulate(s.begin(), s.end(), 0, [](int acc, char c) {
            return acc | (1 << (c - 'a'));
        });
        A[now]++; 
    }

    // calculare suma pe fiecare submasca
    F = A;  SOS_DP_add(F);

    // calculare rezultat 
    int X = 0;
    for (int mask = 0; mask < (1 << 24); mask++) {
        int au_vocale = n - F[(1 << 24) - 1 - mask];
        X ^= (au_vocale * au_vocale); 
    }

    // afisare rezultat
    cout << X << '\n';
    return 0; 
}