#include "graph.cpp"

class Solution {
public:
    static int shortestPathLength(const std::vector<std::vector<int>>& graph) {
        class graph g;
        g.grow(graph.size());
        for(uint x = 0;x < graph.size();x++) {
            for(uint y : graph[x]) {
                g.add_edge(x, y);
            }
        }
        class graph g_transformed;
        g_transformed.grow(graph.size());
        for(uint x = 0;x < graph.size();x++) {
            const auto &bfs = g.bfs_distances({x});
            for(const auto &node : bfs) {
                g_transformed.add_edge(x, node.node, node.distance);
            }
        }
        return g_transformed.traveling_salesman(false).first;
    }
};
