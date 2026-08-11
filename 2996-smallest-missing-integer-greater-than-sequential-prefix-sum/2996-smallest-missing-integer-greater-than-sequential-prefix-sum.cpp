class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = nums.size();

        int sum = nums[0];

        for (int i = 1; i < n && nums[i] == nums[i - 1] + 1; i++) {
            sum += nums[i];
        }

        vector<bool> present(sum + n + 1, false);

        for (int x : nums) {
            if (x <= sum + n)
                present[x] = true;
        }

        while (present[sum])
            sum++;

        return sum;
    }
};