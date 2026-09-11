class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int freq[10] = {};

        for (int d : digits)
            freq[d]++;

        int ans = 0;

        for (int i = 1; i <= 9; i++) {          // hundreds
            if (freq[i] == 0) continue;
            freq[i]--;

            for (int j = 0; j <= 9; j++) {      // tens
                if (freq[j] == 0) continue;
                freq[j]--;

                for (int k = 0; k <= 8; k += 2) { // units (even)
                    if (freq[k] > 0)
                        ans++;
                }

                freq[j]++;
            }

            freq[i]++;
        }

        return ans;
    }
};