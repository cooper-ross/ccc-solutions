#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        g[u].push_back(v); g[v].push_back(u);
    }

    // Iterative DFS to build parent, depth and order (preorder)
    vector<int> parent(n, -1), depth(n, 0);
    vector<int> order; order.reserve(n);
    {
        vector<int> st;
        st.push_back(0);
        parent[0] = -1;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            order.push_back(u);
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            }
        }
    }

    // Preorder index l[u] and inverse t[pos] -> node
    vector<int> l(n), t(n);
    for (int i = 0; i < n; ++i) {
        l[order[i]] = i;
        t[i] = order[i];
    }

    // Subtree size e[u] and es[u] = sum of e[v] for v in subtree(u) (including e[u])
    vector<int> e(n, 1);
    for (int i = n-1; i >= 0; --i) {
        int u = order[i];
        for (int v : g[u]) if (v != parent[u]) e[u] += e[v];
    }
    vector<long long> es(n, 0);
    for (int i = n-1; i >= 0; --i) {
        int u = order[i];
        es[u] = e[u];
        for (int v : g[u]) if (v != parent[u]) es[u] += es[v];
    }

    // Canonical hashing: map sorted vector of child-hashes -> id
    map<vector<int>, int> mp;
    int id = 0;
    vector<int> h(n, -1);
    for (int i = n-1; i >= 0; --i) {
        int u = order[i];
        vector<int> ch;
        ch.reserve(g[u].size());
        for (int v : g[u]) if (v != parent[u]) ch.push_back(h[v]);
        sort(ch.begin(), ch.end());
        auto it = mp.find(ch);
        if (it == mp.end()) {
            mp.emplace(ch, id);
            h[u] = id++;
        } else h[u] = it->second;
    }

    // For each hash id store preorder positions of occurrences and prefix sums of depths
    vector<vector<int>> dv(id);
    vector<vector<long long>> sv(id);
    for (int pos = 0; pos < n; ++pos) {
        int node = t[pos];
        int hid = h[node];
        dv[hid].push_back(pos);
        if (sv[hid].empty()) sv[hid].push_back(depth[node]);
        else sv[hid].push_back(sv[hid].back() + depth[node]);
    }

    // binary lifting table up[j][u] = 2^j-th ancestor of u
    int LOG = 0;
    while ((1 << LOG) <= n) ++LOG;
    vector<vector<int>> up(LOG, vector<int>(n, -1));
    for (int u = 0; u < n; ++u) up[0][u] = parent[u];
    for (int j = 1; j < LOG; ++j) {
        for (int u = 0; u < n; ++u) {
            int mid = up[j-1][u];
            up[j][u] = (mid == -1 ? -1 : up[j-1][mid]);
        }
    }

    // Returns true if shape constraints for node u are satisfied when candidate original-root is rt.
    auto check = [&](int rt, int u)->bool {
        int hid = h[u];
        auto &vec = dv[hid];
        if (vec.empty()) return true; // No occurrences at all -> trivially ok

        int L = l[rt];
        int R = l[rt] + e[rt] - 1; // Inclusive range of preorder indices for subtree(rt)

        // Find first >= L and last <= R
        int lb = int(lower_bound(vec.begin(), vec.end(), L) - vec.begin());
        int ub = int(upper_bound(vec.begin(), vec.end(), R) - vec.begin()) - 1;

        // If no occurrences in the subtree range -> ok
        if (lb >= (int)vec.size() || ub < lb) return true;

        // Now safe to access sv[hid][ub] and sv[hid][lb-1] (guard lb)
        long long sumd = sv[hid][ub] - (lb ? sv[hid][lb-1] : 0LL);
        long long cnt = (long long)(ub - lb + 1);

        // d'_v + 1 = depth[v] - (depth[rt] - 1)
        long long val = sumd - (long long)(depth[rt] - 1) * cnt;

        // Must be <= total occurrences of that shape in the whole tree (vec.size())
        return val <= (long long)vec.size();
    };

    // Mark banned roots using a guarded doubling trick.
    // Any time we encounter a node v that fails, we mark nodes upwards safely.
    vector<char> ban(n, 0);
    for (int u = 0; u < n; ++u) {
        int c = u;
        for (int j = LOG - 1; j >= 0; --j) {
            int v = (c == -1 ? -1 : up[j][c]);
            if (v == -1) continue;
            if (!ban[v] && check(v, u)) {
                c = v;
            } else {
                // Mark path nodes from v upwards until -1 or already banned
                int w = v;
                while (w != -1 && !ban[w]) {
                    ban[w] = 1;
                    w = up[0][w];
                }
            }
        }
    }

    // Valid root r must not be banned and must satisfy es[r] + m == n
    vector<char> okShape(id, 0);
    for (int r = 0; r < n; ++r) {
        if (!ban[r] && es[r] + m == n) okShape[h[r]] = 1;
    }
    int ans = 0;
    for (int i = 0; i < id; ++i) if (okShape[i]) ++ans;
    cout << ans << '\n';
    return 0;
}