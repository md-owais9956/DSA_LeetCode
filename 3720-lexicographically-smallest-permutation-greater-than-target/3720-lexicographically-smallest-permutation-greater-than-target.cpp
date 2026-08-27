class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        int n = s.size();
        int matched = 0;

        // Match target as much as possible
        while (matched < n) {
            int x = target[matched] - 'a';

            if (cnt[x] == 0)
                break;

            cnt[x]--;
            matched++;
        }

        // Start from the last valid position
        int pos = min(matched, n - 1);

        for (; pos >= 0; pos--) {

            // If target[pos] was previously used,
            // put it back.
            if (pos < matched) {
                cnt[target[pos] - 'a']++;
            }

            int cur = target[pos] - 'a';

            // Find smallest character greater than target[pos]
            for (int c = cur + 1; c < 26; c++) {

                if (cnt[c] == 0)
                    continue;

                cnt[c]--;

                string ans = target.substr(0, pos);
                ans += char('a' + c);

                // Add all remaining characters in sorted order
                for (int j = 0; j < 26; j++) {
                    while (cnt[j] > 0) {
                        ans += char('a' + j);
                        cnt[j]--;
                    }
                }

                return ans;
            }
        }

        return "";
    }
};