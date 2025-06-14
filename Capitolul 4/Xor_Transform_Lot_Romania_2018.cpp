/*
    Autor: Ciobanu Dragoș
*/
#include <bits/stdc++.h>
#include <fstream>
#include <cmath>
using namespace std;

/*
    * Problema: Transformarea XOR
    * Descriere: Se cere sa se calculeze suma elementelor pentru fiecare submasca a unui vector de lungime 2^n, folosind transformarea XOR.
    * Solutie: Se foloseste programarea dinamica pe submultimi pentru a calcula suma pe fiecare submasca, folosind operatia XOR.
    * Complexitate: O(n * 2^n)
*/
void SOS_DP_xor(vector<int>& F) {
    int LEN = F.size();
    for (int ind = 0; ind < log2(LEN); ind++)
        for (int mask = 0; mask < LEN; mask++)
            if (mask & (1 << ind))
                F[mask] = F[mask] ^ F[mask ^ (1 << ind)];
}

/*
    * Functie pentru transformarea XOR a unei matrice
    * @param N: numarul de linii
    * @param M: numarul de coloane
    * @param mat: matricea de intrare
    * @param Q: numarul de interogari
    * @param queries: vectorul de interogari
    * @param K_MAX: valoarea maxima a lui K
    * @param outputFile: fisierul de iesire
*/
void xorTransform(int N, int M,
                   const vector<vector<int>>& mat,
                   int Q, const vector<int>& queries,
                   int K_MAX, const string& outputFile) {
    vector<int> B(K_MAX, 0);
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < M; ++j) {
            int k = i | j; 
            B[k] ^= mat[i][j];
        }
    vector<int> F(K_MAX, 0);
    F = B;
    SOS_DP_xor(F);
    ofstream g(outputFile);
    int prev = 0;
    for (int idx = 0; idx < Q; ++idx) {
        int K = queries[idx] ^ prev;
        K &= (K_MAX - 1);
        int ans = F[K]; g << ans << '\n';
        prev = ans;
    }
    g.close();
}

int main() {
    // Citire date de intrare
    int N, M, Q;
    ifstream f("xortransform.in");
    f >> N >> M >> Q;
    vector<vector<int>> mat(N, vector<int>(M));
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < M; ++j) 
            f >> mat[i][j];
        
    // Calculare K_MAX
    int Max = 0;
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < M; ++j) 
            Max = max(Max, i | j);
    int K_MAX_cnt = ceil(log2(Max + 1));
    int K_MAX = 1 << K_MAX_cnt;

    vector<int> queries(Q);
    for (int i = 0; i < Q; ++i) 
        f >> queries[i];
    f.close();
    
    // Apelare functie pentru transformarea XOR
    xorTransform(N, M, mat, Q, queries, K_MAX, "xortransform.out");
    return 0;
}