
class Solution {
public:
    string s;
    int i = 0;

    set<string> parseExpression() {
        set<string> result = parseTerm();

        while (i < s.size() && s[i] == ',') {
            i++; // Skip comma

            set<string> next = parseTerm();

            // Union of both sets
            result.insert(next.begin(), next.end());
        }

        return result;
    }

    set<string> parseTerm() {
        set<string> result = {""};

        while (i < s.size() &&
               s[i] != '}' &&
               s[i] != ',') {

            set<string> current = parseFactor();

            set<string> next;

            // Concatenate every possibility
            for (const string& a : result) {
                for (const string& b : current) {
                    next.insert(a + b);
                }
            }

            result = next;
        }

        return result;
    }

    set<string> parseFactor() {
        set<string> result;

        if (s[i] == '{') {
            i++; // Skip '{'

            result = parseExpression();

            i++; // Skip '}'
        }
        else {
            // Single character
            result.insert(string(1, s[i]));
            i++;
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        i = 0;

        set<string> result = parseExpression();

        return vector<string>(result.begin(), result.end());
    }
};