class Solution {
public:
    int minMoves(vector<int>& nums) {
        int maxm = *max_element(nums.begin(), nums.end());
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        return n * maxm - sum;
    }
};