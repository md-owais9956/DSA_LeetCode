class Solution {
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum, sq, lazy;
    };

    vector<Node> seg;
    int n;

    void apply(int p, int l, int r, long long v) {
        long long len = r - l + 1;
        seg[p].sq = (seg[p].sq + 2LL * v % MOD * seg[p].sum % MOD
                    + len % MOD * v % MOD * v) % MOD;
        seg[p].sum = (seg[p].sum + len * v) % MOD;
        seg[p].lazy = (seg[p].lazy + v) % MOD;
    }

    void push(int p, int l, int r) {
        if (seg[p].lazy == 0 || l == r) return;

        int m = (l + r) / 2;
        long long v = seg[p].lazy;

        apply(p * 2, l, m, v);
        apply(p * 2 + 1, m + 1, r, v);

        seg[p].lazy = 0;
    }

    void update(int p, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return;

        if (ql <= l && r <= qr) {
            apply(p, l, r, 1);
            return;
        }

        push(p, l, r);
        int m = (l + r) / 2;

        update(p * 2, l, m, ql, qr);
        update(p * 2 + 1, m + 1, r, ql, qr);

        seg[p].sum = (seg[p * 2].sum + seg[p * 2 + 1].sum) % MOD;
        seg[p].sq = (seg[p * 2].sq + seg[p * 2 + 1].sq) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        seg.assign(4 * n + 5, {0, 0, 0});

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = last.count(nums[i]) ? last[nums[i]] : -1;

            update(1, 0, n - 1, prev + 1, i);

            last[nums[i]] = i;

            ans = (ans + seg[1].sq) % MOD;
        }

        return (int)ans;
    }
};