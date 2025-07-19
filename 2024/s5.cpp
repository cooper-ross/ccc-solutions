#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    
    vector<vector<int>> a(2, vector<int>(N));
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a[i][j];
        }
    }
    
    long long sum = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < N; j++) {
            sum += a[i][j];
        }
    }
    long long avg = sum;
    
    // Multiply by (2 * N), long long to avoid overflow
    vector<vector<long long>> b(2, vector<long long>(N));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < N; j++) {
            b[i][j] = (long long)a[i][j] * (2 * N);
        }
    }
    
    unordered_map<long long, int> dp;
    dp[0] = 0;
    int ans = 0;
    long long psa = 0;
    long long psb = 0;
    
    for (int i = 0; i < N; i++) {
        psa += b[0][i] - avg;
        psb -= b[1][i] - avg;
        
        int ta = max(ans, (dp.find(psa) != dp.end()) ? dp[psa] + 1 : 0);
        dp[psa] = ta;
        
        int tb = max(ans, (dp.find(psb) != dp.end()) ? dp[psb] + 1 : 0);
        dp[psb] = tb;
        
        ans = max(ta, tb);
    }
    
    cout << ans << endl;
    
    return 0;
}