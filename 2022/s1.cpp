#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    cin >> N;

    long long r = N % 4;
    long long maxY = N / 5;

    if (r > maxY) {
        cout << 0 << endl;
        return 0;
    }

    long long count = (maxY - r) / 4 + 1;
    cout << count << endl;
}