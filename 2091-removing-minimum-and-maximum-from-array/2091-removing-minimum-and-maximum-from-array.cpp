class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int mn = min_element(nums.begin(), nums.end()) - nums.begin();
        int mx = max_element(nums.begin(), nums.end()) - nums.begin();

        int l = min(mn, mx);
        int r = max(mn, mx);

        return min({
            r + 1,             
            n - l,              
            l + 1 + n - r       
        });
    }
};