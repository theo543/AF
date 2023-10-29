#include "graph.cpp"

class Solution {
public:
    static int shortestBridge(const std::vector<std::vector<int>>& grid) {
        uint n = grid.size();
        const std::pair<int, int> dirs[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        graph g;
        g.grow(n * n);
        // add only edges between 1s in order to find components
        for(uint x = 0;x < n;x++) {
            for(uint y = 0;y < n;y++) {
                if(grid[x][y] == 1) {
                    const auto valid_target = [&](const int x, const int y) {
                        return x >= 0 && x < (int)n && y >= 0 && y < (int)n && grid[x][y] == 1;
                    };
                    for(const auto &d : dirs) {
                        const int x2 = x + d.first, y2 = y + d.second;
                        if(valid_target(x2, y2)) {
                            g.add_edge(x * n + y, x2 * n + y2);
                        }
                    }
                }
            }
        }
        std::vector<uint> comp = g.components();
        auto comp_coord = [&](const uint x, const uint y) {
            return comp[x * n + y];
        };
        std::vector<uint> comp_a, comp_b;
        uint comp_a_id = UINT32_MAX, comp_b_id = UINT32_MAX;
        for(uint x = 0;x < grid.size();x++) {
            for(uint y = 0;y < grid.size();y++) {
                if(grid[x][y]) {
                    if(comp_a_id == UINT32_MAX) {
                        comp_a_id = comp_coord(x, y);
                        comp_a.push_back(x * n + y);
                    } else if (comp_coord(x, y) == comp_a_id) {
                        comp_a.push_back(x * n + y);
                    } else {
                        comp_b_id = comp_coord(x, y);
                        comp_b.push_back(x * n + y);
                    }
                }
            }
        }
        g = graph();
        g.grow(n * n);
        // this time add all edges
        for(uint x = 0;x < n;x++) {
            for(uint y = 0;y < n;y++) {
                const auto valid_target = [&](const int x, const int y) {
                    return x >= 0 && x < (int)n && y >= 0 && y < (int)n;
                };
                for(const auto &d : dirs) {
                    const int x2 = x + d.first, y2 = y + d.second;
                    if(valid_target(x2, y2)) {
                        g.add_edge(x * n + y, x2 * n + y2);
                    }
                }
            }
        }
        // start a bfs from any node in comp_a
        std::vector<graph::bfs_result> bfs = g.bfs_distances(comp_a);
        uint min_dist = UINT32_MAX;
        for(auto r : bfs) {
            if(comp[r.node] == comp_b_id) {
                min_dist = std::min(min_dist, r.distance);
            }
        }
        return min_dist - 1;
    }
};
