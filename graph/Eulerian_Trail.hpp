vector<int> EulerianTrail(const int s, vector<vector<int>> &g, const bool directed) {
        function<void (int, vector<int> &)> dfs = & {
                while (!g[u].empty()) {
                        int v = g[u].back();
                        g[u].pop_back();
                        if (!directed) {
                                for (int i = 0; i < g[v].size(); i ++) {
                                        if (g[v][i] == u) {
                                                g[v].erase(g[v].begin() + i);
                                                break;
                                        }
                                }
                        }
                        dfs(v, trail);
                }
                trail.push_back(u);
        };
        vector<int> trail;
        dfs(s, trail);
        reverse(trail.begin(), trail.end());
        return trail;
}