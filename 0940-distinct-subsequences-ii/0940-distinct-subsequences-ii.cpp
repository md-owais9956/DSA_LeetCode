class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;

        long long dp[26] = {};

        long long total = 0;

        for (char ch : s) {
            int idx = ch - 'a';

            long long newSubseq = (total + 1) % MOD;

            total = (total - dp[idx] + newSubseq + MOD) % MOD;

            dp[idx] = newSubseq;
        }

        return total;
    }
};