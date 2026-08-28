class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        vector<int> cnt(26, 0);
        for (char c : s)
            cnt[c - 'a']++;

        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        vector<int> halfCnt(26);
        for (int i = 0; i < 26; i++)
            halfCnt[i] = cnt[i] / 2;

        int m = n / 2;

        auto makePalindrome = [&](string half) {
            string res = half;

            if (n % 2)
                res += mid;

            reverse(half.begin(), half.end());
            res += half;

            return res;
        };

        string p = target.substr(0, m);

        vector<int> rem = halfCnt;
        bool possible = true;

        for (char c : p) {
            if (rem[c - 'a'] == 0) {
                possible = false;
                break;
            }
            rem[c - 'a']--;
        }

        if (possible) {
            string candidate = makePalindrome(p);

            if (candidate > target)
                return candidate;
        }


        for (int i = m - 1; i >= 0; i--) {

            vector<int> left = halfCnt;
            bool ok = true;

            for (int j = 0; j < i; j++) {
                int x = p[j] - 'a';

                if (left[x] == 0) {
                    ok = false;
                    break;
                }

                left[x]--;
            }

            if (!ok)
                continue;

            for (int c = (p[i] - 'a') + 1; c < 26; c++) {

                if (left[c] == 0)
                    continue;

                string half = p.substr(0, i);
                half += char('a' + c);

                left[c]--;

               
                for (int x = 0; x < 26; x++) {
                    while (left[x] > 0) {
                        half += char('a' + x);
                        left[x]--;
                    }
                }

                return makePalindrome(half);
            }
        }

        return "";
    }
};