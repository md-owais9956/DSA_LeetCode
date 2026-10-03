class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);

        int ans = 0;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                st.push(i);
            }
            else {
                st.pop();

                if (st.empty()) {
                    // New invalid boundary
                    st.push(i);
                }
                else {
                    // Length of current valid substring
                    ans = max(ans, i - st.top());
                }
            }
        }

        return ans;
    }
};