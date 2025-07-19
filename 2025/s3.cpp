#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, c, q;
    cin >> n >> c >> q;

    vector<set<pair<long long, int>, greater<>>> groups(c + 1);
    vector<int> color(n + 1);
    vector<long long> score(n + 1);

    for (int i = 1; i <= c; ++i) groups[i].insert({0, 0});
    for (int i = 1; i <= n; ++i) {
        int col; long long s;
        cin >> col >> s;
        color[i] = col;
        score[i] = s;
        groups[col].insert({s, i});
    }

    long long sum = 0;
    set<pair<long long, int>> top, second;

    auto update_state = [&](int col, bool add) {
        auto it = groups[col].begin(), it2 = next(it);
        if (!groups[col].empty()) {
            if (!add) {
                sum -= it->first;
                top.erase(*it);
                if (it2 != groups[col].end()) second.erase(*it2);
            } else {
                sum += it->first;
                top.insert(*it);
                if (it2 != groups[col].end()) second.insert(*it2);
            }
        }
    };

    for (int i = 1; i <= c; ++i) update_state(i, true);

    auto get_best = [&]() {
        if (!second.empty()) return max(sum, sum + prev(second.end())->first - top.begin()->first);
        return sum;
    };

    cout << get_best() << '\n';

    while (q--) {
        int t, id, val;
        cin >> t >> id >> val;
        if (t == 1) {
            int old_c = color[id], new_c = val;
            long long s = score[id];
            update_state(old_c, false);
            update_state(new_c, false);
            groups[old_c].erase({s, id});
            groups[new_c].insert({s, id});
            color[id] = new_c;
            update_state(old_c, true);
            update_state(new_c, true);
        } else {
            int col = color[id];
            long long old_s = score[id];
            update_state(col, false);
            groups[col].erase({old_s, id});
            groups[col].insert({val, id});
            score[id] = val;
            update_state(col, true);
        }
        cout << get_best() << '\n';
    }
}