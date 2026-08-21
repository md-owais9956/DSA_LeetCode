class Solution {
public:
    using ll = long long;

    ll gcd(ll a, ll b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    ll lcm(ll a, ll b) {
        return a / gcd(a, b) * b;
    }

    long long findKthSmallest(vector<int>& coins, int k) {

        // Remove redundant coins
        sort(coins.begin(), coins.end());

        vector<ll> c;

        for (ll x : coins) {
            bool redundant = false;

            for (ll y : c) {
                if (x % y == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant)
                c.push_back(x);
        }

        int n = c.size();
        int total = 1 << n;

        // lcm[mask] = LCM of all coins in this subset
        vector<ll> lcmVal(total, 1);

        for (int mask = 1; mask < total; mask++) {

            int bit = __builtin_ctz(mask);
            int prev = mask & (mask - 1);

            lcmVal[mask] = lcm(lcmVal[prev], c[bit]);
        }

        // Count numbers <= x divisible by at least one coin
        auto count = [&](ll x) {

            ll ans = 0;

            for (int mask = 1; mask < total; mask++) {

                if (lcmVal[mask] > x)
                    continue;

                ll cnt = x / lcmVal[mask];

                // Odd subset -> add
                // Even subset -> subtract
                if (__builtin_popcount(mask) & 1)
                    ans += cnt;
                else
                    ans -= cnt;
            }

            return ans;
        };

        // Binary search
        ll low = 1;
        ll high = c[0] * (ll)k;

        while (low < high) {

            ll mid = low + (high - low) / 2;

            if (count(mid) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};