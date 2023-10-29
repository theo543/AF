#include "graph.cpp"
#include <algorithm>

class Solution {
public:
    static std::vector<int> eventualSafeNodes(const std::vector<std::vector<int>>& input) {
        graph g;
        g.grow(input.size());
        for(uint x = 0;x < input.size();x++) {
            for(auto y : input[x]) {
                g.add_edge(y, x);
            }
        }
        auto ts = g.topsort();
        std::sort(ts.begin(), ts.end());
        return {ts.begin(), ts.end()};
    }
};
