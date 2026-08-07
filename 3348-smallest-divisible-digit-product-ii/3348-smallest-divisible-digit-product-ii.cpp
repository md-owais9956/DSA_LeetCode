class Solution {
public:
    string smallestNumber(string num, long long t) {
        vector<int> req(8, 0);
        long long temp_t = t;
        int primes[] = {2, 3, 5, 7};
        
        for (int p : primes) {
            while (temp_t % p == 0) {
                req[p]++;
                temp_t /= p;
            }
        }
        
        if (temp_t > 1) {
            return "-1";
        }

        int digit_primes[10][8] = {0};
        for (int d = 1; d <= 9; ++d) {
            int val = d;
            for (int p : primes) {
                while (val % p == 0) {
                    digit_primes[d][p]++;
                    val /= p;
                }
            }
        }

        auto get_min_digits = [&](const vector<int>& rem_req) {
            int c2 = rem_req[2], c3 = rem_req[3], c5 = rem_req[5], c7 = rem_req[7];

            int d9 = c3 / 2; c3 %= 2;
            int d8 = c2 / 3; c2 %= 3;
            int d4 = c2 / 2; c2 %= 2;

            int d6 = 0;
            if (c2 == 1 && c3 == 1) {
                c2 = 0; c3 = 0; d6 = 1;
            } else if (c3 == 1 && d4 == 1) {
                c3 = 0; d4 = 0; c2 = 1; d6 = 1;
            }

            string digits = "";
            digits.append(c2, '2');
            digits.append(c3, '3');
            digits.append(d4, '4');
            digits.append(c5, '5');
            digits.append(d6, '6');
            digits.append(c7, '7');
            digits.append(d8, '8');
            digits.append(d9, '9');
            return digits;
        };

        int n = num.length();

        bool num_has_zero = false;
        vector<int> cur_req(8, 0);
        for (char ch : num) {
            if (ch == '0') {
                num_has_zero = true;
                break;
            }
            int d = ch - '0';
            for (int p : primes) {
                cur_req[p] += digit_primes[d][p];
            }
        }

        if (!num_has_zero) {
            bool valid = true;
            for (int p : primes) {
                if (cur_req[p] < req[p]) {
                    valid = false;
                    break;
                }
            }
            if (valid) return num;
        }

        vector<vector<int>> prefix_req(n + 1, vector<int>(8, 0));
        int first_zero = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
            int d = num[i] - '0';
            prefix_req[i + 1] = prefix_req[i];
            for (int p : primes) {
                prefix_req[i + 1][p] += digit_primes[d][p];
            }
        }

        for (int i = n - 1; i >= 0; --i) {
            if (i > first_zero) continue;

            int orig_digit = num[i] - '0';

            for (int next_digit = orig_digit + 1; next_digit <= 9; ++next_digit) {
                vector<int> rem_req(8, 0);
                for (int p : primes) {
                    int needed = req[p] - prefix_req[i][p] - digit_primes[next_digit][p];
                    rem_req[p] = max(0, needed);
                }

                string min_digits = get_min_digits(rem_req);
                int space_left = (n - 1) - i;

                if ((int)min_digits.length() <= space_left) {
                    int ones_count = space_left - min_digits.length();
                    string res = num.substr(0, i);
                    res += to_string(next_digit);
                    res.append(ones_count, '1');
                    res += min_digits;
                    return res;
                }
            }
        }

        string min_digits = get_min_digits(req);
        int target_len = max(n + 1, (int)min_digits.length());
        int ones_count = target_len - min_digits.length();

        string res = "";
        res.append(ones_count, '1');
        res += min_digits;
        return res;
    }
};