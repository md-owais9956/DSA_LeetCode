
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n), tree(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> last(26, -1);

        // Find new parents using original tree
        function<void(int)> dfs = [&](int u) {
            int c = s[u] - 'a';

            int prev = last[c];

            int newParent = parent[u];

            if (prev != -1) {
                newParent = prev;
            }

            if (u != 0) {
                tree[newParent].push_back(u);
            }

            last[c] = u;

            for (int v : adj[u]) {
                dfs(v);
            }

            last[c] = prev;
        };

        dfs(0);

        // Calculate subtree sizes
        vector<int> ans(n, 1);

        function<int(int)> calculate = [&](int u) {
            for (int v : tree[u]) {
                ans[u] += calculate(v);
            }

            return ans[u];
        };

        calculate(0);

        return ans;
    }
};
