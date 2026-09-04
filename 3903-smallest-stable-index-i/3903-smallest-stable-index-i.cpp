class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> sufMin(n);
        sufMin[n - 1] = nums[n - 1];

        // suffix minimum
        for (int i = n - 2; i >= 0; i--) {
            sufMin[i] = min(nums[i], sufMin[i + 1]);
        }

        int prefMax = nums[0];

        for (int i = 0; i < n; i++) {
            prefMax = max(prefMax, nums[i]);

            if ((long long)prefMax - sufMin[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};