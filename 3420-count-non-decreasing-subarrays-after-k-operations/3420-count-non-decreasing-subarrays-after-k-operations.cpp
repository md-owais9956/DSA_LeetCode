
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 1;

        while ((1 << LOG) <= n)
            LOG++;

        vector<int> nxt(n + 1, n);
        vector<int> st;

        // Next Greater Element
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.back()] <= nums[i])
                st.pop_back();

            if (!st.empty())
                nxt[i] = st.back();

            st.push_back(i);
        }

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + nums[i];

        // Binary lifting tables
        vector<vector<int>> jump(LOG, vector<int>(n + 1, n));
        vector<vector<long long>> sum(LOG, vector<long long>(n + 1, 0));

        for (int i = 0; i < n; i++) {
            jump[0][i] = nxt[i];
            sum[0][i] = 1LL * nums[i] * (nxt[i] - i);
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i <= n; i++) {
                int mid = jump[j - 1][i];

                jump[j][i] = jump[j - 1][mid];

                sum[j][i] = sum[j - 1][i] +
                            sum[j - 1][mid];
            }
        }

        // Sum of prefix maximums in [l, r]
        auto getMaxSum = [&](int l, int r) -> long long {
            int cur = l;
            int end = r + 1;
            long long res = 0;

            for (int j = LOG - 1; j >= 0; j--) {
                int to = jump[j][cur];

                if (to <= end) {
                    res += sum[j][cur];
                    cur = to;
                }
            }

            if (cur < end)
                res += 1LL * nums[cur] * (end - cur);

            return res;
        };

        long long ans = 0;

        // Binary search for every starting index
        for (int l = 0; l < n; l++) {
            int low = l;
            int high = n - 1;
            int best = l - 1;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                long long cost =
                    getMaxSum(l, mid) -
                    (pref[mid + 1] - pref[l]);

                if (cost <= k) {
                    best = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            ans += best - l + 1;
        }

        return ans;
    }
};
