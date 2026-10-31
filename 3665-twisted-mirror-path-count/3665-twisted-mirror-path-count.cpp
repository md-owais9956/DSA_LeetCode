
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<long long> dp(n, 0);
        dp[0] = 1;

        for (int i = 0; i < m; i++) {
            long long right = 0;

            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {
                    swap(right, dp[j]);
                }
                else {
                    long long ways = (right + dp[j]) % MOD;

                    right = ways;
                    dp[j] = ways;
                }
            }
        }

        return dp[n - 1] == 0 ? 0 : 
               (int)((dp[n - 1]) % MOD);
    }
};
