class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<string> ans;
        int prevEnd = -1;

        for (int i = 0; i < n; i++) {

            if (i != first[s[i] - 'a'])
                continue;

            int l = i;
            int r = last[s[i] - 'a'];
            bool valid = true;

            for (int j = l; j <= r; j++) {
                int c = s[j] - 'a';

                if (first[c] < l) {
                    valid = false;
                    break;
                }

                r = max(r, last[c]);
            }

            if (!valid)
                continue;

            string cur = s.substr(l, r - l + 1);

            if (l > prevEnd) {
                ans.push_back(cur);
                prevEnd = r;
            }
            else {
                if (r < prevEnd) {
                    ans.back() = cur;
                    prevEnd = r;
                }
            }
        }

        return ans;
    }
};