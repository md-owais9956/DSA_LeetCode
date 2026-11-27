
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; i++) {
            int factor = items[i][0];
            int price = items[i][1];

            int freeItems = 0;

            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % factor == 0) {
                    freeItems++;
                }
            }

            // Buy the first copy (0/1 knapsack)
            for (int b = budget; b >= price; b--) {
                dp[b] = max(dp[b],
                            dp[b - price] + 1 + freeItems);
            }

            // Buy additional copies (unbounded knapsack)
            for (int b = price; b <= budget; b++) {
                dp[b] = max(dp[b],
                            dp[b - price] + 1);
            }
        }

        return dp[budget];
    }
};
