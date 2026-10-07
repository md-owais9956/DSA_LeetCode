class Solution {
public:
    vector<string> ans;

    void solve(string &s, int index, int left, int right, int open,
               string current) {

        if (index == s.size()) {
            if (left == 0 && right == 0 && open == 0) {
                ans.push_back(current);
            }
            return;
        }

        char c = s[index];

        // Option 1: Remove current parenthesis
        if (c == '(' && left > 0) {
            solve(s, index + 1, left - 1, right, open, current);
        }

        if (c == ')' && right > 0) {
            solve(s, index + 1, left, right - 1, open, current);
        }

        // Option 2: Keep current character
        if (c != '(' && c != ')') {
            solve(s, index + 1, left, right, open, current + c);
        }
        else if (c == '(') {
            solve(s, index + 1, left, right, open + 1, current + c);
        }
        else if (c == ')' && open > 0) {
            solve(s, index + 1, left, right, open - 1, current + c);
        }
    }

    vector<string> removeInvalidParentheses(string s) {

        int left = 0, right = 0;

        // Find minimum removals required
        for (char c : s) {
            if (c == '(') {
                left++;
            }
            else if (c == ')') {
                if (left > 0)
                    left--;
                else
                    right++;
            }
        }

        solve(s, 0, left, right, 0, "");

        // Remove duplicates
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};