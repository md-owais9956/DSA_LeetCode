class Solution {
public:
    int minMoves(vector<int>& nums) {

        int maxElement = *max_element(nums.begin(), nums.end());
        int count = 0;
        for(int i : nums){
            if( i == maxElement ) continue;
            count += maxElement - i;
            
        }
        
        return count;
    }
};