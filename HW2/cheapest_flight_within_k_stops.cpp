#include "graph.cpp"

using std::vector;

class Solution {
public:
    static int findCheapestPrice(int n, const vector<vector<int>>& flights, int src_, int dst_, int k_) {
        const uint src = src_, dst = dst_, k = k_;
        graph g;
        g.grow(n * (k + 2));
        for(uint dist = 0;dist <= k;dist++) {
            for(const auto &v : flights) {
                g.add_edge(v.at(0) + dist * n, v.at(1) + (dist + 1) * n, v.at(2));
            }
        }
        auto res = g.dijkstra(src);
        uint result = UINT32_MAX;
        for(uint i = 0;i <= (k+1);i++) {
            result = std::min(result, res.distances.at(dst + i * n));
        }
        if(result == UINT32_MAX) {
            return -1;
        }
        return result;
    }
};
