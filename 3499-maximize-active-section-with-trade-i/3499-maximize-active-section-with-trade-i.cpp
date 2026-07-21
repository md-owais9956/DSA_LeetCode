class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int ones = 0;
        for (char c : s)
            if (c == '1') ones++;

        string t = "1" + s + "1";
        int n = t.size();

        int ans = ones;

        int i = 0;
        int prevZero = 0;

        while (i < n) {
            char ch = t[i];
            int j = i;
            while (j < n && t[j] == ch) j++;

            int len = j - i;

            if (ch == '0') {
                prevZero = len;
            } else {
                // Interior 1-block?
                if (i > 0 && j < n && t[i - 1] == '0' && t[j] == '0') {
                    int k = j;
                    while (k < n && t[k] == '0') k++;
                    int nextZero = k - j;

                    ans = max(ans, ones + prevZero + nextZero);
                }
            }

            i = j;
        }

        return ans;
    }
};