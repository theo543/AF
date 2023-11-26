#include <fstream>
#include "graph.cpp"

int main() {
    std::ifstream in("bile.in");
    std::ofstream out("bile.out");
    int n;
    in >> n;
    graph g;
    g.grow(n * n);
    g.init_union_find();
    struct operations {
        int x, y;
        uint max_component_prior_to_this;
    };
    std::vector<operations> edges;
    for(int i = 0;i < n * n;i++) {
        int x, y;
        in >> x >> y;
        x--; y--;
        edges.push_back({x, y, 0});
    }
    uint current_max = 0;
    std::vector<std::vector<bool>> added_yet = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
    for(int i = edges.size() - 1;i >= 0;i--) {
        edges[i].max_component_prior_to_this = current_max;
        added_yet[edges[i].x][edges[i].y] = true;
        constexpr std::pair<int, int> dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for(const auto &d : dirs) {
            int x1 = edges[i].x + d.first, y1 = edges[i].y + d.second;
            if(x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || !added_yet[x1][y1]) {
                continue;
            }
            g.add_edge(edges[i].x * n + edges[i].y, x1 * n + y1);
        }
        // if the current_max grew, the new max component includes this node
        uint new_max = g.find_size(edges[i].x * n + edges[i].y);
        current_max = std::max(current_max, new_max);
    }
    for(uint i = 0;i < edges.size();i++) {
        out << edges[i].max_component_prior_to_this << '\n';
    }
}
