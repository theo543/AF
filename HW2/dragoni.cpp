#include <fstream>

#include "graph.cpp"

std::vector<uint> reachable_with_distance(const int n, const std::vector<edge> &edges, const sint max_distance, const uint start) {
    graph g;
    g.grow(n);
    for(const auto &e : edges) {
        if(e.cost > max_distance) {
            continue;
        }
        g.add_edge(e.src, e.dst, e.cost);
        g.add_edge(e.dst, e.src, e.cost);
    }
    const auto bfs = g.bfs_distances({start});
    std::vector<uint> result;
    for(const auto &r : bfs) {
        result.push_back(r.node);
    }
    return result;
}

int main() {
    std::ifstream in("dragoni.in");
    std::ofstream out("dragoni.out");
    int request;
    int n, m;
    in >> request >> n >> m;
    std::vector<uint> distance_upgrades(n);
    for(int i = 0;i < n;i++) {
        in >> distance_upgrades[i];
    }
    std::vector<edge> base_edges(m);
    for(int i = 0;i < m;i++) {
        uint from, to;
        sint cost;
        in >> from >> to >> cost;
        base_edges[i] = {from - 1, to - 1, cost};
    }
    if(request == 1) {
        const auto bfs = reachable_with_distance(n, base_edges, distance_upgrades[0], 0);
        uint max_reachable = 0;
        for(const auto &node : bfs) {
            max_reachable = std::max(max_reachable, distance_upgrades[node]);
        }
        out << max_reachable << '\n';
    } else {
        graph g;
        g.grow(n * n);
        for(int i = 0;i < n;i++) {
            for(const auto &edge : base_edges) {
                if((uint)edge.cost <= distance_upgrades[i]) {
                    uint src = i * n + edge.src, dst = i * n + edge.dst;
                    g.add_edge(src, dst, edge.cost);
                    g.add_edge(dst, src, edge.cost);
                }
            }
            if(i != n - 1) {
                for(int node = 0;node < n;node++) {
                    g.add_edge(i * n + node, node * n + node, 0);
                }
            }
        }
        const auto dfs = g.dijkstra(0);
        uint result = UINT64_MAX;
        for(int i = 0;i < n;i++) {
            int node = i * n + n - 1;
            if(dfs.distances[node] != UINT64_MAX) {
                result = std::min(result, dfs.distances[node]);
            }
        }
        assert(result != UINT64_MAX);
        out << result << '\n';
    }
}
