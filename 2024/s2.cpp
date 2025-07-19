#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, N;
    cin >> T >> N;
    
    for (int t = 0; t < T; t++) {
        string s;
        cin >> s;
        
        unordered_map<char, int> freq;
        for (char c : s) {
            freq[c]++;
        }
        
        bool alternates = true;
        bool prevHeavy = (freq[s[0]] > 1);
        
        for (int i = 1; i < N; i++) {
            bool currHeavy = (freq[s[i]] > 1);
            if (currHeavy == prevHeavy) {
                alternates = false;
                break;
            }
            prevHeavy = currHeavy;
        }
        
        cout << (alternates ? "T" : "F") << "\n";
    }
    
    return 0;
}