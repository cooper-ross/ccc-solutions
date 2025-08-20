#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    
    vector<int> vals;
    vector<pair<int, int>> ranges;
    
    int l = 0, r = 0, val = B[0];
    vals.push_back(val);
    
    for (int i = 1; i < n; i++) {
        if (B[i] == val) {
            r++;
        } else {
            ranges.push_back({l, r});
            l = r = i;
            val = B[i];
            vals.push_back(val);
        }
    }
    ranges.push_back({l, r});
    
    // Find each segment value in A
    int cur = 0;
    vector<pair<int, int>> swipeL, swipeR;
    
    for (int i = 0; i < n && cur < vals.size(); i++) {
        if (A[i] == vals[cur]) {
            if (ranges[cur].first < i) {
                swipeL.push_back({ranges[cur].first, i});
            }
            if (ranges[cur].second > i) {
                swipeR.push_back({i, ranges[cur].second});
            }
            cur++;
        }
    }
    
    if (cur == vals.size()) {
        cout << "YES\n" << swipeL.size() + swipeR.size() << "" << endl;
        for (auto& p : swipeL) {
            cout << "L " << p.first << " " << p.second << "" << endl;
        }
        for (int i = swipeR.size() - 1; i >= 0; i--) {
            cout << "R " << swipeR[i].first << " " << swipeR[i].second << "" << endl;
        }
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}