class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        for (auto &x : knowledge) {
            mp[x[0]] = x[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                int j = i + 1;
                string key;

                while (s[j] != ')') {
                    key += s[j];
                    j++;
                }

                // Replace with value if key exists
                if (mp.count(key))
                    ans += mp[key];
                else
                    ans += "?";

                // Skip everything until ')'
                i = j;
            }
            else {
                ans += s[i];
            }
        }

        return ans;
    }
};