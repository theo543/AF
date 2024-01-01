#include <fstream>
#include <vector>

#include "graph.cpp"

#if __cplusplus >= 201703L
#define FALLTHROUGH [[fallthrough]]
#else
#define FALLTHROUGH __attribute__((fallthrough))
#endif

const std::pair<uint, uint> range_1_dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const std::pair<uint, uint> range_2_dirs[] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {2, 0}, {-2, 0}, {0, 2}, {0, -2}};

void read_foxes__init_surface(graph &surface, uint m, uint n, std::ifstream &in) {
    uint k;
    in >> k;
    // padding of 2
    bool matrix[204][204] = {};
    for(uint x = 0;x < m;x++) {
        for(uint y = 0;y < n;y++) {
            matrix[x + 2][y + 2] = true;
        }
    }
    for(uint x = 0, xv, yv, range;x < k;x++) {
        in >> xv >> yv >> range;
        xv = xv - 1 + 2;
        yv = yv - 1 + 2;
        assert(range <= 2);
        switch(range) {
            case 2:
                for(const auto &dir : range_2_dirs) {
                    matrix[xv + dir.first][yv + dir.second] = false;
                }
                FALLTHROUGH;
            case 1:
                for(const auto &dir : range_1_dirs) {
                    matrix[xv + dir.first][yv + dir.second] = false;
                }
                FALLTHROUGH;
            case 0:
                matrix[xv][yv] = false;
                break;
        }
    }
    surface.grow(m * n);
    for(uint x = 0;x < m;x++) {
        for(uint y = 0;y < n;y++) {
            if(!matrix[x + 2][y + 2]) {
                continue;
            }
            for(const auto &dir : range_1_dirs) {
                if(matrix[x + (2 + dir.first)][y + (2 + dir.second)]) {
                    surface.add_edge(x * n + y, (x + dir.first) * n + (y + dir.second));
                }
            }
        }
    }
}

int main() {
    std::ifstream in("cartite.in");
    std::ofstream out("cartite.out");
    uint p;
    uint m, n;
    uint xc, yc;
    graph surface;

    in >> p >> m >> n >> xc >> yc;
    xc--; yc--;
    read_foxes__init_surface(surface, m, n, in);

    uint coords_to_node_id[200][200];
    std::pair<uint, uint> node_id_to_coords[105 * 2 + 1];
    std::vector<std::pair<uint, uint>> edges;
    uint nodes = 0;
    std::fill(&coords_to_node_id[0][0], &coords_to_node_id[0][0] + 200 * 200, UINT64_MAX);
    std::fill(node_id_to_coords, node_id_to_coords + 105 * 2 + 1, std::pair<uint, uint>{UINT64_MAX, UINT64_MAX});

    const auto ensure_node_exists = [&coords_to_node_id, &node_id_to_coords, &nodes](uint x, uint y) {
        if(coords_to_node_id[x][y] == UINT64_MAX) {
            coords_to_node_id[x][y] = nodes;
            node_id_to_coords[nodes] = {x, y};
            nodes++;
        }
    };

    uint g;
    in >> g;
    for(uint x = 0, xa, ya, xb, yb;x < g;x++) {
        in >> xa >> ya >> xb >> yb;
        xa--; ya--; xb--; yb--;
        ensure_node_exists(xa, ya);
        ensure_node_exists(xb, yb);
        edges.push_back({coords_to_node_id[xa][ya], coords_to_node_id[xb][yb]});
        edges.push_back({coords_to_node_id[xb][yb], coords_to_node_id[xa][ya]});
    }

    uint entry_x, entry_y, entry_dist = UINT64_MAX;
    const auto &bfs = surface.bfs_distances({xc * n + yc});
    for(const auto &result : bfs) {
        uint y = result.node % n;
        uint x = result.node / n;
        if(coords_to_node_id[x][y] == UINT64_MAX) {
            continue;
        }
        if(result.distance < entry_dist) {
            entry_x = x;
            entry_y = y;
            entry_dist = result.distance;
            goto found_entry;
        }
    }
    out << "Error: entry not found.\n";
    return EXIT_FAILURE;

    found_entry:
    if(p == 1) {
        out << entry_x + 1 << ' ' << entry_y + 1 << ' ' << entry_dist << '\n';
        return 0;
    }

    graph tunnels;
    tunnels.grow(nodes);
    while(!edges.empty()) {
        const auto &edge = edges.back();
        tunnels.add_edge(edge.first, edge.second);
        edges.pop_back();
    }
    const auto &cycle = tunnels.eulerian_path(coords_to_node_id[entry_x][entry_y], true);
    assert(p == 2);
    assert(cycle.size() == g + 1);
    for(const auto &node : cycle) {
        const auto &coords = node_id_to_coords[node];
        out << coords.first + 1 << ' ' << coords.second + 1 << '\n';
    }
}
