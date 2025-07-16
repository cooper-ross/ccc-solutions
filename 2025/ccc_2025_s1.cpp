#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    long long A, B, X, Y;
    cin >> A >> B >> X >> Y;
    
    long long p1 = 2 * ((A + X) + max(B, Y));
    long long p2 = 2 * (max(A, X) + (B + Y));
    
    cout << min(p1, p2) << endl;
    
    return 0;
}