#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
using namespace std;
 
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
 
// A[mask] = numarul de stringuri care au vocalele din masca de biti i
int A[(1 << 24)];

// dp[mask] = numarul de vocale din masca de biti mask
int dp[(1 << 24)]; 
 
int main() {
    fast
    
    // citire date de intrare
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        // now = masca de biti care retine vocalele din stringul s
        int now = 0;
        for (int j = 0; j < s.size(); j++) {
            int x = s[j] - 'a';
            now |= (1 << x);
        }
        A[now]++;
    }

    // dp = A
    for (int mask = 0; mask < (1 << 24); mask++)
        dp[mask] = A[mask];

    // SOS DP
    for (int i = 0; i < 24; i++)
        for (int mask = 0; mask < (1 << 24); mask++)
            if (mask & (1 << i))     
                dp[mask] += dp[mask ^ (1 << i)];

    // X = suma xor patratul numarului de stringuri cu cel putin o vocala din masca mask
    int X = 0;
    for (int mask = 0; mask < (1 << 24); mask++) {
        // have_vocale = numarul de stringuri care contin cel putin o vocala din masca de biti mask
        int have_vocals = n - dp[(1 << 24) - 1 - mask];
        X ^= (have_vocals * have_vocals);
    }
    cout << X << '\n';
    return 0; 
}