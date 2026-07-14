class Solution {
public:
    static const int MOD = 1000000007;

    int subsequencePairCount(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());

        // dp[g1][g2] = number of ways where gcd(seq1)=g1, gcd(seq2)=g2
        vector<vector<int>> dp(mx + 1, vector<int>(mx + 1, 0));
        dp[0][0] = 1;

        for (int num : nums) {
            vector<vector<int>> ndp(mx + 1, vector<int>(mx + 1, 0));

            for (int g1 = 0; g1 <= mx; g1++) {
                for (int g2 = 0; g2 <= mx; g2++) {
                    if (dp[g1][g2] == 0) continue;

                    // Skip current element
                    ndp[g1][g2] = (ndp[g1][g2] + dp[g1][g2]) % MOD;

                    // Put in first subsequence
                    int ng1 = std::gcd(g1, num);
                    ndp[ng1][g2] = (ndp[ng1][g2] + dp[g1][g2]) % MOD;

                    // Put in second subsequence
                    int ng2 = std::gcd(g2, num);
                    ndp[g1][ng2] = (ndp[g1][ng2] + dp[g1][g2]) % MOD;
                }
            }

            dp = move(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= mx; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return ans;
    }
};