class Solution {
public:
    static const int MAXX = 2048;

    void fwht(vector<long long>& a) {
        int n = a.size();
        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += len << 1) {
                for (int j = 0; j < len; j++) {
                    long long u = a[i + j];
                    long long v = a[i + j + len];
                    a[i + j] = u + v;
                    a[i + j + len] = u - v;
                }
            }
        }
    }

    int uniqueXorTriplets(vector<int>& nums) {
        vector<long long> f(MAXX, 0);

        unordered_set<int> st(nums.begin(), nums.end());
        for (int x : st) f[x] = 1;

        fwht(f);

        for (int i = 0; i < MAXX; i++)
            f[i] = f[i] * f[i] * f[i];

        fwht(f);

        int ans = 0;
        for (int i = 0; i < MAXX; i++) {
            if (f[i] != 0) ans++;
        }

        return ans;
    }
};