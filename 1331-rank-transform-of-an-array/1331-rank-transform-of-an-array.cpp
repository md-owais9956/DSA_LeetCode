class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> temp = arr;
        sort(temp.begin(), temp.end());

        unordered_map<int, int> rank;
        int r = 1;

        for (int x : temp) {
            if (!rank.count(x))
                rank[x] = r++;
        }

        for (int &x : arr)
            x = rank[x];

        return arr;
    }
};