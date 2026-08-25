class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        for (int x = k; ; x += k) {
            bool found = false;

            for (int num : nums) {
                if (num == x) {
                    found = true;
                    break;
                }
            }

            if (!found)
                return x;
        }
    }
};