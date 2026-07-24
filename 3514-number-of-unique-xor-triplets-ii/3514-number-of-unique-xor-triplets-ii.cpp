class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;

        unordered_set<int> pairXor;
        unordered_set<int> ans;

        // XOR of every pair of distinct elements
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                pairXor.insert(nums[i] ^ nums[j]);
            }
        }

        // (a ^ b) ^ c
        for (int x : pairXor) {
            for (int v : nums) {
                ans.insert(x ^ v);
            }
        }

        // Triplets where all three indices are the same
        for (int v : nums) {
            ans.insert(v);
        }

        return ans.size();
    }
};