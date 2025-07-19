#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    
    vector<int> hats(N);
    for (int i = 0; i < N; i++) {
        cin >> hats[i];
    }
    
    int count = 0;
    for (int i = 0; i < N; i++) {
        int opposite = (i + N/2) % N;
        if (hats[i] == hats[opposite]) {
            count++;
        }
    }
    
    cout << count << endl;
    return 0;
}