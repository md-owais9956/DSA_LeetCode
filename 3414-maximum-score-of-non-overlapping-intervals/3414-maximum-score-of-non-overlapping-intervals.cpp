
class Solution {
public:
    struct Interval {
        int l, r, w, idx;
    };

    using State = pair<long long, vector<int>>;

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<Interval> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        // Sort by starting position.
        sort(a.begin(), a.end(), [](const Interval& A,
                                    const Interval& B) {
            return A.l < B.l;
        });

        vector<int> starts(n);

        for (int i = 0; i < n; i++) {
            starts[i] = a[i].l;
        }

        // next[i] = first interval whose start > a[i].r
        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {
            nxt[i] = upper_bound(
                starts.begin() + i + 1,
                starts.end(),
                a[i].r
            ) - starts.begin();
        }

        vector<vector<State>> dp(
            n + 1,
            vector<State>(5, {-1, {}})
        );

        vector<vector<bool>> vis(n + 1, vector<bool>(5, false));

        auto better = [](const State& A, const State& B) {
            if (A.first != B.first)
                return A.first > B.first;

            return A.second < B.second;
        };

        function<State(int, int)> solve = [&](int pos, int left) -> State {
            if (pos == n || left == 0) {
                return {0, {}};
            }

            if (vis[pos][left]) {
                return dp[pos][left];
            }

            vis[pos][left] = true;

            // Option 1: Skip the current interval.
            State skip = solve(pos + 1, left);

            // Option 2: Take the current interval.
            State take = solve(nxt[pos], left - 1);

            take.first += a[pos].w;
            take.second.push_back(a[pos].idx);

            // Sort original indices for lexicographical comparison.
            sort(take.second.begin(), take.second.end());

            if (better(take, skip)) {
                dp[pos][left] = take;
            } else {
                dp[pos][left] = skip;
            }

            return dp[pos][left];
        };

        return solve(0, 4).second;
    }
};