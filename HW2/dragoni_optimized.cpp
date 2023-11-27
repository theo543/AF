#include <fstream>
#include <vector>
#include <queue>

struct edge {
    int to;
    int cost;
};

struct lazy_djikstra_node {
    int node;
    int dragon;
    int distance;
    bool operator<(const lazy_djikstra_node &other) const {
        return distance > other.distance;
    }
};

int main() {
    std::ifstream in("dragoni.in");
    std::ofstream out("dragoni.out");
    int request;
    int n, m;
    in >> request >> n >> m;
    std::vector<std::vector<edge>> edges(n);
    std::vector<int> distance_upgrades(n);
    for(int i = 0;i < n;i++) {
        in >> distance_upgrades[i];
    }
    std::vector<edge> base_edges(m);
    for(int i = 0;i < m;i++) {
        int from, to, cost;
        in >> from >> to >> cost;
        edges[from - 1].push_back({to - 1, cost});
        edges[to - 1].push_back({from - 1, cost});
    }
    if(request == 1) {
        std::queue<int> q;
        std::vector<bool> visited(n, false);
        int max_reachable = distance_upgrades[0];
        q.push(0);
        visited[0] = true;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            for(const auto &edge : edges[node]) {
                if(edge.cost > distance_upgrades[0] || visited[edge.to]) {
                    continue;
                }
                visited[edge.to] = true;
                q.push(edge.to);
                max_reachable = std::max(max_reachable, distance_upgrades[edge.to]);
            }
        }
        out << max_reachable << '\n';
    } else {
        std::vector<int> distances(n * n, INT32_MAX);
        std::priority_queue<lazy_djikstra_node> q;
        distances[0] = 0;
        q.push({0, 0, 0});
        while(!q.empty()) {
            const auto node = q.top();
            q.pop();
            if(node.distance != distances[node.dragon * n + node.node]) {
                continue;
            }
            for(const auto &edge : edges[node.node]) {
                if(edge.cost > distance_upgrades[node.dragon]) {
                    continue;
                }
                int relaxed_distance = node.distance + edge.cost;
                int relaxed_node = node.dragon * n + edge.to;
                if(distances[relaxed_node] > relaxed_distance) {
                    distances[relaxed_node] = relaxed_distance;
                    q.push({edge.to, node.dragon, relaxed_distance});
                }
            }
            // also the upgrade edge
            int relaxed_distance = node.distance;
            // switch to current node's dragon
            int relaxed_node = (node.node) * n + node.node;
            if(relaxed_distance < distances[relaxed_node]) {
                distances[relaxed_node] = relaxed_distance;
                q.push({node.node, node.node, relaxed_distance});
            }
        }
        int result = INT32_MAX;
        for(int i = 0;i < n;i++) {
            int node = i * n + n - 1;
            if(distances[node] != INT32_MAX) {
                result = std::min(result, distances[node]);
            }
        }
        if(result == INT32_MAX) {
            __builtin_trap();
        }
        out << result << '\n';
    }
}
