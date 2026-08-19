class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int s = seat[1];

            if (s >= 2 && s <= 9) {
                mp[row] |= (1 << (s - 2));
            }
        }

        int ans = (n - mp.size()) * 2;

        for (auto &[row, mask] : mp) {
            bool left  = (mask & 15) == 0;   
            bool right = (mask & 240) == 0;
            bool mid   = (mask & 60) == 0;   

            if (left) ans++;
            if (right) ans++;

           
            if (!left && !right && mid)
                ans++;
        }

        return ans;
    }
};