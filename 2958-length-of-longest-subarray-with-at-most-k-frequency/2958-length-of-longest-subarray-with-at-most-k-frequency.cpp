class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        freq.reserve(nums.size() * 2);
        freq.max_load_factor(0.7);

        int left = 0;
        int ans = 0;

        for (int right = 0; right < nums.size(); ++right) {
            ++freq[nums[right]];

            while (freq[nums[right]] > k) {
                --freq[nums[left]];
                ++left;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};