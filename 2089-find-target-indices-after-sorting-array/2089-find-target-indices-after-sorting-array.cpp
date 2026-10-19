class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {

        int cntles{0};
        int cnteql{0};
        
        vector<int> indx;

        for(auto it : nums){
            if(it < target){
                cntles++;
            }
            if (it == target){
                cnteql++;
            }
        }
        for(int i = 0; i < cnteql; i++){
            indx.push_back(i + cntles);
        }
        return indx;
    }
};