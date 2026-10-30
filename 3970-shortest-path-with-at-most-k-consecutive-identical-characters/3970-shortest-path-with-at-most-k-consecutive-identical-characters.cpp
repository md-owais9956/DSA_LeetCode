
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {

        vector<vector<pair<int, int>>> adj(n);

        // Build directed weighted graph
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
        }

        const long long INF = LLONG_MAX;

        // dist[node][count]
        vector<vector<long long>> dist(
            n, vector<long long>(k + 1, INF)
        );

        // {distance, node, consecutive count}
        priority_queue<
            tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>
        > pq;

        // Starting node itself contributes one character
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {

            auto [d, u, cnt] = pq.top();
            pq.pop();

            // Ignore outdated states
            if (d != dist[u][cnt])
                continue;

            // Destination reached optimally
            if (u == n - 1)
                return (int)d;

            for (auto &[v, w] : adj[u]) {

                int newCnt;

                if (labels[u] == labels[v])
                    newCnt = cnt + 1;
                else
                    newCnt = 1;

                // Invalid consecutive sequence
                if (newCnt > k)
                    continue;

                long long newDist = d + w;

                if (newDist < dist[v][newCnt]) {

                    dist[v][newCnt] = newDist;

                    pq.push({
                        newDist,
                        v,
                        newCnt
                    });
                }
            }
        }

        return -1;
    }
};
