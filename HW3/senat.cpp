#include <fstream>
#include <sstream>

#include "graph.cpp"

int main() {
    std::ifstream in("senat.in");
    std::ofstream out("senat.out");
    std::string n_str, m_str;
    getline(in, n_str);
    getline(in, m_str);
    uint n = std::stoi(n_str), m = std::stoi(m_str);
    std::vector<uint> left(n), right(m);
    std::vector<std::pair<uint, uint>> edges;
    std::iota(left.begin(), left.end(), 0);
    std::iota(right.begin(), right.end(), n);
    std::string line;
    for(uint x = 0; x < m; x++) {
        getline(in, line);
        std::istringstream in_line(line);
        uint left_node;
        while(in_line >> left_node) {
            edges.push_back({left_node - 1, n + x});
        }
    }
    const auto &matching = solve_bipartite(left, right, edges, false);
    if(matching.maximum_matching.size() != m) {
        out << 0 << '\n';
        return 0;
    }
    for(const auto &edge : matching.maximum_matching) {
        right[edge.second - n] = edge.first;
    }
    for(uint president : right) {
        out << president + 1 << '\n';
    }
}
