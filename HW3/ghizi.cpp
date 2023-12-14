#include <fstream>
#include <map>

#include "graph.cpp"

int main() {
    std::ifstream in("ghizi.in");
    std::map<std::pair<uint, uint>, uint> interval_guides;
    graph g;
    g.grow(102);
    uint n, k;
    in >> n >> k;
    g.add_edge(101, 0, k);
    for(uint x = 0, a, b;x < n;x++) {
        in >> a >> b;
        interval_guides[std::pair<uint, uint>{a, b}] = x + 1;
        g.add_edge(a, b, 1);
    }
    const auto flow = g.edmonds_karp(101, 100);
    std::ofstream out("ghizi.out");
    out << flow.total << '\n';
    for(const auto &node : flow.edges) {
        for(const auto &edge : node) {
            if(edge.flow != 0 && edge.src != 101 && edge.dst != 101) {
                assert(edge.flow > 0);
                out << interval_guides.at(std::pair<uint, uint>(edge.src, edge.dst)) << ' ';
            }
        }
    }
    out << '\n';
}
