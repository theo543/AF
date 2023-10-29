#include "graph.cpp"

class Solution {
public:
    static bool possibleBipartition(const int n, const std::vector<std::vector<int>>& dislikes) {
        graph g;
        g.grow(n);
        for(const auto &v : dislikes) {
            g.add_edge(v[0] - 1, v[1] - 1);
            g.add_edge(v[1] - 1, v[0] - 1);
        }
        auto part = g.bipartition();
        return part.first;
    }
};
