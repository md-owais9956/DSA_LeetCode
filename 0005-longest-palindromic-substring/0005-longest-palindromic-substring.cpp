class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<int> d1(n), d2(n);
        int start = 0, maxLen = 0;

        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);

            while (i - k >= 0 && i + k < n &&
                   s[i - k] == s[i + k])
                k++;

            d1[i] = k;
            int len = 2 * k - 1;

            if (len > maxLen) {
                maxLen = len;
                start = i - k + 1;
            }

            if (i + k - 1 > r) {
                l = i - k + 1;
                r = i + k - 1;
            }
        }

        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);

            while (i - k - 1 >= 0 && i + k < n &&
                   s[i - k - 1] == s[i + k])
                k++;

            d2[i] = k;
            int len = 2 * k;

            if (len > maxLen) {
                maxLen = len;
                start = i - k;
            }

            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }

        return s.substr(start, maxLen);
    }
};