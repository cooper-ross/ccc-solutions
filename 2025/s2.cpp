#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    long long c;
    cin >> s >> c;
    
    vector<pair<char, long long>> pattern;
    long long total_length = 0;

    for (int i = 0; i < s.length(); ) {
        char ch = s[i];
        i++;

        long long count = 0;
        while (i < s.length() && isdigit(s[i])) {
            count = count * 10 + (s[i] - '0');
            i++;
        }
        
        pattern.push_back({ch, count});
        total_length += count;
    }
    
    long long pos = c % total_length;
    long long current_pos = 0;
    for (auto& p : pattern) {
        if (current_pos + p.second > pos) {
            cout << p.first << endl;
            return 0;
        }
        current_pos += p.second;
    }
    
    return 0;
}