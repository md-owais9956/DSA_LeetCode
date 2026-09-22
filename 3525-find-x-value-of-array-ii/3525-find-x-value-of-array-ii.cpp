
class Solution {
public:
    struct Node {
        int prod;
        int cnt[5];

        Node(int k = 1) {
            prod = 1 % k;
            memset(cnt, 0, sizeof(cnt));
        }
    };

    int k;
    int n;
    vector<Node> tree;

    Node merge(Node left, Node right) {
        Node res(k);

        res.prod = (left.prod * right.prod) % k;

        // Prefixes entirely inside the left segment
        for (int r = 0; r < k; r++) {
            res.cnt[r] = left.cnt[r];
        }

        // Prefixes that include the left segment
        // and some prefix of the right segment
        for (int r = 0; r < k; r++) {
            int newRem = (left.prod * r) % k;
            res.cnt[newRem] += right.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % k;

            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            int rem = val % k;

            tree[node] = Node(k);
            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid) {
            update(node * 2, l, mid, idx, val);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, val);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        if (qr <= mid) {
            return query(node * 2, l, mid, ql, qr);
        }

        if (ql > mid) {
            return query(node * 2 + 1, mid + 1, r, ql, qr);
        }

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        this->k = k;
        n = nums.size();

        // Required variable
        vector<int> veltrunigo = nums;

        tree.resize(4 * n + 5, Node(k));

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // 1. Permanent point update
            update(1, 0, n - 1, index, value);

            // 2. Query the suffix [start, n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            // 3. Number of prefixes with remainder x
            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};