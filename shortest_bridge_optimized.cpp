#include <vector>
#include <cassert>

class Solution {
public:
    static int shortestBridge(const std::vector<std::vector<int>>& grid) {

        struct bfs_coord;
        struct coord {
            int x, y;
        };
        struct bfs_coord {
            int x, y;
            int dist;
        };

        const coord dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        const int n = grid.size();

        const auto in_bounds = [n](coord c) {
            return c.x >= 0 && c.x < n && c.y >= 0 && c.y < n;
        };

        std::vector<std::vector<char>> island (n, std::vector<char>(n, 0));
        std::vector<bfs_coord> bfs;
        bfs.reserve(n * n);
        char found_so_far = 0;

        for(int x = 0;x < n;x++) {
            for(int y = 0;y < n;y++) {
                if(grid[x][y] == 1 && island[x][y] == 0) {
                    assert(found_so_far < 2);
                    found_so_far++;
                    bfs.clear();
                    bfs.push_back({x, y, -1});
                    island[x][y] = found_so_far;
                    for(size_t b_i = 0; b_i < bfs.size(); b_i++) {
                        bfs_coord node = bfs[b_i];
                        for(const auto dir : dirs) {
                            coord neighbour = {node.x + dir.x, node.y + dir.y};
                            if(!in_bounds(neighbour) || grid[neighbour.x][neighbour.y] == 0) {
                                continue;
                            }
                            char &n_i = island[neighbour.x][neighbour.y];
                            if(n_i == 0) {
                                n_i = found_so_far;
                                bfs.push_back({neighbour.x, neighbour.y, -1}); // don't care about distance
                            } else {
                                // islands are separate
                                assert(n_i == found_so_far);
                            }
                        }
                    }
                }
            }
        }

        assert(found_so_far == 2);
        bfs.clear();
        for(int x = 0;x < n;x++) {
            for(int y = 0;y < n;y++) {
                if(island[x][y] == 1) {
                    bfs.push_back({x, y, 0});
                }
            }
        }
        for(size_t x = 0;x < bfs.size();x++) {
            bfs_coord node = bfs[x];
            for(const auto d : dirs) {
                coord neighbour {node.x + d.x, node.y + d.y};
                if(!in_bounds(neighbour)) {
                    continue;
                }
                auto &n_i = island[neighbour.x][neighbour.y];
                if(n_i == 2) {
                    // found shortest path
                    int answer = node.dist;
                    return answer;
                } else if(n_i == 0) {
                    n_i = 1;
                    bfs.push_back({neighbour.x, neighbour.y, node.dist + 1});
                }
            }
        }
        assert(false);
        return -1;
    }
};
