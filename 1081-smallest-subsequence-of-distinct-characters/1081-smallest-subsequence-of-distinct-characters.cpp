class Solution {
public:
    string smallestSubsequence(string s) {
        int freq[26] = {0};
        bool vis[26] = {false};
        string ans;

        for (char c : s)
            freq[c - 'a']++;

        for (char c : s) {
            freq[c - 'a']--;

            if (vis[c - 'a'])
                continue;

            while (!ans.empty() &&
                   ans.back() > c &&
                   freq[ans.back() - 'a'] > 0) {

                vis[ans.back() - 'a'] = false;
                ans.pop_back();
            }

            ans.push_back(c);
            vis[c - 'a'] = true;
        }

        return ans;
    }
};