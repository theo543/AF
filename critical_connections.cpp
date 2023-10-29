#include "graph.cpp"

class Solution {
public:
    static std::vector<std::vector<int>> criticalConnections(const int n, const std::vector<std::vector<int>>& connections) {
        if(n == 0) {
            return {};
        }
        // load the edges into a graph to DFS it
        graph g;
        g.grow(n);
        for(const auto &v : connections) {
            g.add_edge(v[0], v[1]);
            g.add_edge(v[1], v[0]);
        }
        // DFS the graph from an arbitrary root
        auto res = g.dfs_open_close(0);
        // check which edges are critical
        std::vector<std::vector<int>> result;
        for(const auto &v : connections) {
            // the rule is that for an edge A<->B where A is the parent (lower open time)
            // if close(B) > open(A) then the edge is critical
            int a = v[0], b = v[1];
            if(res[a].open > res[b].open) {
                std::swap(a, b);
            }
            if(res[b].close > res[a].open) {
                result.push_back({a, b});
            }
        }
        return result;
    }
};
