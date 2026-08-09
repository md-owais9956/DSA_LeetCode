class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M, vector<int>& piles) {

        if (i == n)
            return 0;

        if (n - i <= 2 * M)
            return suffix[i];

        if (dp[i][M] != -1)
            return dp[i][M];

        int best = 0;

        for (int X = 1; X <= 2 * M; X++) {

            int taken = suffix[i] - suffix[i + X];

            int opponent = solve(
                i + X,
                max(M, X),
                piles
            );

            best = max(best, taken - opponent + suffix[i + X]);
        }

        return dp[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {

        n = piles.size();

        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1, piles);
    }
};