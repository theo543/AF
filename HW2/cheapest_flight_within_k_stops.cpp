#include <iostream>

#include "graph.cpp"

using std::vector;

class Solution {
public:
    static int findCheapestPrice(int n, const vector<vector<int>>& flights, int src_, int dst_, int k_) {
        const uint32_t src = src_, dst = dst_, k = k_;
        graph g;
        g.grow(n);
        for(const auto &v : flights) {
            g.add_edge(v.at(0), v.at(1), v.at(2));
        }
        auto bfs = g.bfs_distances({src});
        std::vector<bool> too_far(n, false);
        for(const auto &b : bfs) {
            if(b.distance > k) {
                too_far[b.node] = true;
            }
        }
        g = graph();
        g.grow(n);
        for(const auto &v : flights) {
            if(too_far.at(v.at(0))) {
                continue;
            }
            g.add_edge(v.at(0), v.at(1), v.at(2));
        }
        auto dijkstra = g.dijkstra(src);
        if(dijkstra.distances.at(dst) == UINT32_MAX) {
            return -1;
        }
        return dijkstra.distances.at(dst);
    }
};
