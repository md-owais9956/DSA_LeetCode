class Solution {
public:
    using ll = long long;

    ll gcd(ll a, ll b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    ll lcm(ll a, ll b) {
        return a / gcd(a, b) * b;
    }

    ll count(ll x, vector<int>& coins) {
        int n = coins.size();
        ll ans = 0;

        // All non-empty subsets
        for (int mask = 1; mask < (1 << n); mask++) {
            ll L = 1;
            int bits = 0;
            bool valid = true;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    L = lcm(L, (ll)coins[i]);

                    // L is already larger than x
                    if (L > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid)
                continue;

            if (bits % 2 == 1)
                ans += x / L;
            else
                ans -= x / L;
        }

        return ans;
    }

    long long findKthSmallest(vector<int>& coins, int k) {

        ll low = 1;
        ll high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            ll mid = low + (high - low) / 2;

            if (count(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};