class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();

        unordered_map<int, pair<int, int>> mp;

        // Store first and last occurrence
        for (int i = 0; i < n; i++) {
            if (!mp.count(nums[i])) {
                mp[nums[i]] = {i, i};
            } else {
                mp[nums[i]].second = i;
            }
        }

        int ans = -1;

        for (auto& [x, p] : mp) {
            int first = p.first;
            int last = p.second;

            int L = max(0, first - k + 1);
            int R = min(last, n - k);

            int count = R - L + 1;

            if (count == 1) {
                ans = max(ans, x);
            }
        }

        return ans;
    }
};