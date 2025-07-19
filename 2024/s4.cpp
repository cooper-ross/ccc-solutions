#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<bool> vis;
vector<char> ans;
map<pair<int,int>, int> roadMap;

void dfs(int cur, bool red) {
    vis[cur] = true;
    for (int nxt : graph[cur]) {
        if (!vis[nxt]) {
            if (red) {
                ans[roadMap[{cur, nxt}]] = 'R';
            } else {
                ans[roadMap[{cur, nxt}]] = 'B';
            }
            dfs(nxt, !red);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    graph.resize(n + 1);
    vis.resize(n + 1, false);
    ans.resize(m, 'G');
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        roadMap[{u, v}] = i;
        roadMap[{v, u}] = i;
    }
    
    for (int u = 1; u <= n; u++) {
        if (!vis[u]) {
            dfs(u, true);
        }
    }
    
    for (char c : ans) {
        cout << c;
    }
    cout << endl;
    
    return 0;
}