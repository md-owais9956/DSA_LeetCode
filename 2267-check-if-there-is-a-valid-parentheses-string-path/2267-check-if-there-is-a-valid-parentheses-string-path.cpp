class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        if ((m + n - 1) % 2 != 0)
            return false;

        vector<vector<vector<bool>>> dp(
            m,
            vector<vector<bool>>(n, vector<bool>(m + n, false))
        );

        if (grid[0][0] == ')')
            return false;

        dp[0][0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                for (int balance = 0; balance <= m + n; balance++) {

                    // Previous balance depends on current character
                    int prev;

                    if (grid[i][j] == '(')
                        prev = balance - 1;
                    else
                        prev = balance + 1;

                    if (prev < 0 || prev > m + n)
                        continue;

                    // From top
                    if (i > 0 && dp[i - 1][j][prev])
                        dp[i][j][balance] = true;

                    // From left
                    if (j > 0 && dp[i][j - 1][prev])
                        dp[i][j][balance] = true;
                }
            }
        }

        return dp[m - 1][n - 1][0];
    }
};