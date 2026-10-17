
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        mp.max_load_factor(0.7f);
        mp.reserve(nums.size());

        for (int i = 0, n = nums.size(); i < n; ++i) {
            auto it = mp.find(target - nums[i]);

            if (it != mp.end())
                return {it->second, i};

            mp[nums[i]] = i;
        }

        return {};
    }
};
