class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suf[j] = position where word2[j] can be matched
        // in a valid suffix match.
        vector<int> suf(m, -1);

        int p = n - 1;

        for (int j = m - 1; j >= 0; j--) {
            while (p >= 0 && word1[p] != word2[j])
                p--;

            if (p < 0)
                break;

            suf[j] = p;
            p--;
        }

        vector<int> ans;
        ans.reserve(m);

        int j = 0;
        bool changed = false;

        for (int i = 0; i < n && j < m; i++) {

            // Normal matching
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            }

            // Use the one allowed modification
            else if (!changed) {

                // Last character -> no suffix remains
                if (j == m - 1) {
                    ans.push_back(i);
                    j++;
                    changed = true;
                }

                // Remaining suffix must be matchable
                else if (suf[j + 1] != -1 &&
                         i < suf[j + 1]) {
                    ans.push_back(i);
                    j++;
                    changed = true;
                }
            }
        }

        if (j != m)
            return {};

        return ans;
    }
};