#include <fstream>

#include "graph.cpp"

int main() {
    std::ifstream in("paznici.in");
    std::ofstream out("paznici.out");
    uint n, m;
    in >> n >> m;
    std::vector<uint> left, right;
    std::vector<char> letter(n + m);
    for(uint x = 0;x < n;x++) {
        left.push_back(x);
        letter[x] = 'A' + x;
    }
    for(uint x = 0;x < m;x++) {
        letter[n + x] = 'a' + x;
        right.push_back(n + x);
    }
    std::vector<std::pair<uint, uint>> edges;
    for(uint x = 0;x < n;x++) {
        for(uint y = 0;y < m;y++) {
            char edge;
            in >> edge;
            if(edge == '1') {
                edges.push_back({x, n + y});
            }
        }
    }
    const auto &result = solve_bipartite(left, right, edges, true);
    for(uint node : result.minimum_vertex_cover) {
        out << letter[node];
    }
}
