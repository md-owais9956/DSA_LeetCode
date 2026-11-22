
class Solution {
public:
    bool checkString(string s) {
        bool foundB = false;

        for (char c : s) {
            if (c == 'b') {
                foundB = true;
            }
            else if (foundB) {
                return false;
            }
        }

        return true;
    }
};
