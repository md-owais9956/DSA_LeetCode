
class Solution {
    static constexpr long long MOD = 1'000'000'007;
    vector<long long> fact;

    long long solve(vector<int>& nums, int l, int r) {
        if (r - l <= 1) return 1;

        int root = nums[l];
        int mid = l + 1;

        for (int i = l + 1; i <= r; ++i) {
            if (nums[i] < root) {
                // Partition into left and right subtrees
            }
        }

        vector<int> left, right;
        for (int i = l + 1; i <= r; ++i) {
            if (nums[i] < root) left.push_back(nums[i]);
            else right.push_back(nums[i]);
        }

        long long ways = comb(left.size() + right.size(), left.size());
        ways = ways * solve(left, 0, (int)left.size() - 1) % MOD;
        ways = ways * solve(right, 0, (int)right.size() - 1) % MOD;

        return ways;
    }

    long long modPow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    long long comb(int n, int k) {
        return fact[n] * modPow(fact[k], MOD - 2) % MOD
                    * modPow(fact[n - k], MOD - 2) % MOD;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        fact.assign(n + 1, 1);

        for (int i = 1; i <= n; ++i)
            fact[i] = fact[i - 1] * i % MOD;

        return (solve(nums, 0, n - 1) - 1 + MOD) % MOD;
    }
};
