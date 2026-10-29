
class Solution {
    static constexpr int LOG = 16 + 1;

    vector<vector<int>> adj, up;
    vector<int> tin, tout, depth, parent, sz;
    vector<int> pref;
    int timer = 0;

    vector<int> seg, lazy;

    void apply(int node, int val) {
        seg[node] ^= val;
        lazy[node] ^= val;
    }

    void push(int node) {
        if (lazy[node] != 0) {
            apply(node * 2, lazy[node]);
            apply(node * 2 + 1, lazy[node]);
            lazy[node] = 0;
        }
    }

    void update(int node, int l, int r,
                int ql, int qr, int val) {
        if (ql <= l && r <= qr) {
            apply(node, val);
            return;
        }

        push(node);
        int mid = (l + r) / 2;

        if (ql <= mid)
            update(node * 2, l, mid, ql, qr, val);

        if (qr > mid)
            update(node * 2 + 1, mid + 1, r,
                   ql, qr, val);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    int pointQuery(int node, int l, int r, int pos) {
        if (l == r)
            return seg[node];

        push(node);
        int mid = (l + r) / 2;

        if (pos <= mid)
            return pointQuery(node * 2, l, mid, pos);

        return pointQuery(node * 2 + 1, mid + 1, r, pos);
    }

    void buildTree(int n, const string& s) {
        parent.assign(n, -1);
        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        sz.assign(n, 1);
        pref.assign(n, 0);

        vector<int> order;
        order.reserve(n);
        vector<int> st = {0};
        parent[0] = 0;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            tin[u] = timer++;
            order.push_back(u);

            pref[u] = (u == 0 ? 0 : pref[parent[u]])
                      ^ (1 << (s[u] - 'a'));

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            }
        }

        for (int i = n - 1; i > 0; --i) {
            int u = order[i];
            sz[parent[u]] += sz[u];
        }

        for (int u = 0; u < n; ++u)
            tout[u] = tin[u] + sz[u] - 1;

        up.assign(LOG, vector<int>(n));
        for (int u = 0; u < n; ++u)
            up[0][u] = parent[u];

        for (int k = 1; k < LOG; ++k) {
            for (int u = 0; u < n; ++u) {
                up[k][u] = up[k - 1][up[k - 1][u]];
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];

        for (int k = 0; k < LOG; ++k) {
            if (diff & (1 << k))
                u = up[k][u];
        }

        if (u == v) return u;

        for (int k = LOG - 1; k >= 0; --k) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }

        return parent[u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        timer = 0;
        buildTree(n, s);

        seg.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        for (int u = 0; u < n; ++u) {
            update(1, 0, n - 1, tin[u], tin[u], pref[u]);
        }

        vector<bool> ans;

        for (const string& q : queries) {
            string type;
            int u;
            string third;

            stringstream ss(q);
            ss >> type >> u >> third;

            if (type == "update") {
                char c = third[0];

                int delta = (1 << (s[u] - 'a'))
                          ^ (1 << (c - 'a'));

                if (delta != 0) {
                    update(1, 0, n - 1,
                           tin[u], tout[u], delta);

                    s[u] = c;
                }
            } else {
                int v = stoi(third);
                int w = lca(u, v);

                int maskU = pointQuery(
                    1, 0, n - 1, tin[u]);

                int maskV = pointQuery(
                    1, 0, n - 1, tin[v]);

                int mask = maskU ^ maskV
                         ^ (1 << (s[w] - 'a'));

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};
