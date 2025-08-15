#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int X;
    cin >> X;
    vector<pair<string, string>> together(X);
    for (int i = 0; i < X; i++) {
        cin >> together[i].first >> together[i].second;
    }

    int Y;
    cin >> Y;
    vector<pair<string, string>> separate(Y);
    for (int i = 0; i < Y; i++) {
        cin >> separate[i].first >> separate[i].second;
    }

    int G;
    cin >> G;

    unordered_map<string, int> groupOf;
    for (int g = 0; g < G; g++) {
        string a, b, c;
        cin >> a >> b >> c;
        groupOf[a] = g;
        groupOf[b] = g;
        groupOf[c] = g;
    }

    int violations = 0;

    // Check "must be together"
    for (auto &p : together) {
        if (groupOf[p.first] != groupOf[p.second]) {
            violations++;
        }
    }

    // Check "must be separate"
    for (auto &p : separate) {
        if (groupOf[p.first] == groupOf[p.second]) {
            violations++;
        }
    }

    cout << violations << endl;
    return 0;
}
