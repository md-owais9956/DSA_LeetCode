class Solution {
public:
    int stoneGameV(vector<int>& a) {
        int n = a.size();

        vector<vector<int>> dp(n, vector<int>(n, 0));
        vector<vector<int>> mx(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
            mx[i][i] = a[i];

        for (int r = 1; r < n; r++) {

            int mid = r;
            int sum = a[r];
            int right = 0;

            for (int l = r - 1; l >= 0; l--) {

                sum += a[l];

                while (mid > l &&
                       (right + a[mid]) * 2 <= sum) {
                    right += a[mid];
                    mid--;
                }

                // Equal
                if (right * 2 == sum) {
                    dp[l][r] = mx[l][mid];
                }

                // Left side is smaller
                if (mid != l) {
                    dp[l][r] = max(dp[l][r],
                                   mx[l][mid - 1]);
                }

                // Right side is smaller
                if (mid != r) {
                    dp[l][r] = max(dp[l][r],
                                   mx[r][mid + 1]);
                }

                mx[l][r] = max(mx[l][r - 1],
                                dp[l][r] + sum);

                mx[r][l] = max(mx[r][l + 1],
                                dp[l][r] + sum);
            }
        }

        return dp[0][n - 1];
    }
};