
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        // Step 1: Find maximum factor and minimum price
        int maxF = 0;
        long long minP = LLONG_MAX;

        for (auto& item : items) {
            maxF = max(maxF, item[0]);
            minP = min(minP, (long long)item[1]);
        }

        // Step 2: Count frequency of every factor
        vector<int> freq(maxF + 1, 0);

        for (auto& item : items) {
            freq[item[0]]++;
        }

        // Step 3: Count eligible free-item types
        vector<int> gain(maxF + 1, 0);

        for (int i = 1; i <= maxF; i++) {
            for (int j = i; j <= maxF; j += i) {
                gain[i] += freq[j];
            }
            gain[i]--; // Exclude the item itself
        }

        // Step 4: Sort items by price
        sort(items.begin(), items.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        long long ans = 0;
        long long remaining = budget;

        // Step 5: Buy profitable bonus copies
        for (auto& item : items) {
            int factor = item[0];
            long long price = item[1];

            if (price > 2 * minP)
                break;

            long long available = gain[factor];

            long long take = min(available, remaining / price);

            ans += 2 * take;
            remaining -= take * price;
        }

        // Step 6: Spend remaining budget on cheapest items
        ans += remaining / minP;

        return (int)ans;
    }
};
