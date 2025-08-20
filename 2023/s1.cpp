#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int c;
    cin >> c;

    int* row1 = new int[c];
    int* row2 = new int[c];

    int total = 0;

    for (int i = 0; i < c; i++) {
        cin >> row1[i];
        total += row1[i] * 3; // Add 3 if wet tile (row1[i] == 1), 0 if dry
    }

    for (int i = 0; i < c; i++) {
        cin >> row2[i];
        total += row2[i] * 3;
    }

    for (int i = 0; i < c; i += 2) {
        total -= (row1[i] & row2[i]) << 1; // Subtract 2 if both are 1
    }

    for (int i = 1; i < c; i++) {
        total -= (row1[i] & row1[i-1]) << 1;
        total -= (row2[i] & row2[i-1]) << 1;
    }

    cout << total;
    
    return 0;
}