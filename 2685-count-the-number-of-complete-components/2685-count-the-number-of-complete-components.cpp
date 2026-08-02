class Solution {
public:
    vector<vector<int>> adj;
    vector<int> vis;

    void dfs(int node, vector<int>& comp) {
        vis[node] = 1;
        comp.push_back(node);

        for (int nei : adj[node]) {
            if (!vis[nei])
                dfs(nei, comp);
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        adj.resize(n);
        vis.assign(n, 0);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                vector<int> comp;
                dfs(i, comp);

                int nodes = comp.size();
                int degreeSum = 0;

                for (int node : comp)
                    degreeSum += adj[node].size();

                if (degreeSum == nodes * (nodes - 1))
                    ans++;
            }
        }

        return ans;
    }
};