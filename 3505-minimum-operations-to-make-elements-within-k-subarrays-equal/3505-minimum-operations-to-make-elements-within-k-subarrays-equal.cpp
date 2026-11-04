
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> low, high;
        long long lowSum = 0, highSum = 0;

        vector<long long> cost(n - x + 1);

        auto rebalance = [&]() {
            int target = (low.size() + high.size() + 1) / 2;

            while ((int)low.size() > target) {
                int val = *low.rbegin();
                low.erase(prev(low.end()));
                lowSum -= val;

                high.insert(val);
                highSum += val;
            }

            while ((int)low.size() < target) {
                int val = *high.begin();
                high.erase(high.begin());
                highSum -= val;

                low.insert(val);
                lowSum += val;
            }
        };

        auto add = [&](int val) {
            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                lowSum += val;
            } else {
                high.insert(val);
                highSum += val;
            }
        };

        auto remove = [&](int val) {
            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                lowSum -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                highSum -= val;
            }
        };

        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            rebalance();

            if (i >= x - 1) {
                long long median = *low.rbegin();

                long long leftCost =
                    median * low.size() - lowSum;

                long long rightCost =
                    highSum - median * high.size();

                cost[i - x + 1] = leftCost + rightCost;
            }
        }

        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {

                dp[i][j] = dp[i - 1][j];

                if (i >= x && dp[i - x][j - 1] != INF) {
                    dp[i][j] = min(
                        dp[i][j],
                        dp[i - x][j - 1] + cost[i - x]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
