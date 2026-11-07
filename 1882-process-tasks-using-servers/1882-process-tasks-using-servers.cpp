class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        using P = pair<int, int>;
        using T = tuple<long long, int, int>;

        // {weight, index}
        priority_queue<P, vector<P>, greater<P>> available;

        // {freeTime, weight, index}
        priority_queue<T, vector<T>, greater<T>> busy;

        int n = servers.size();
        int m = tasks.size();

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);

        long long time = 0;

        for (int i = 0; i < m; i++) {

            time = max(time, (long long)i);

            // Move all completed servers to available heap
            while (!busy.empty() && get<0>(busy.top()) <= time) {

                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If no server is available, jump to earliest free time
            if (available.empty()) {

                time = get<0>(busy.top());

                while (!busy.empty() && get<0>(busy.top()) == time) {

                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Select the best server
            auto [weight, index] = available.top();
            available.pop();

            ans[i] = index;

            // Update server's next available time
            busy.push({
                time + tasks[i],
                weight,
                index
            });
        }

        return ans;
    }
};