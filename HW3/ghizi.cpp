#include <fstream>
#include <algorithm>
#include <map>

#include "graph.cpp"

int main() {
    std::ifstream in("ghizi.in");
    std::map<std::pair<uint, uint>, std::vector<uint>> interval_guides;
    graph g;
    g.grow(102);
    uint n, k;
    in >> n >> k;
    g.add_edge(101, 0, k);
    for(uint x = 0, a, b;x < n;x++) {
        in >> a >> b;
        interval_guides[std::pair<uint, uint>{a, b}].push_back(x + 1);
    }
    for(const auto &pair : interval_guides) {
        const auto &interval = pair.first;
        const auto &guides = pair.second;
        g.add_edge(interval.first, interval.second, guides.size());
    }
    const auto flow = g.edmonds_karp(101, 100);
    assert(flow.total == k);
    std::ofstream out("ghizi.out");
    std::vector<int> guides;
    for(const auto &node : flow.edges) {
        for(const auto &edge : node) {
            if(edge.flow != 0 && edge.src != 101 && edge.dst != 101) {
                assert(edge.flow > 0);
                auto &vec = interval_guides.at(std::pair<uint, uint>(edge.src, edge.dst));
                for(sint x = 0;x < edge.flow;x++) {
                    guides.push_back(vec.at(x));
                }
            }
        }
    }
    out << guides.size() << '\n';
    std::sort(guides.begin(), guides.end());
    for(const auto guide : guides) {
        out << guide << ' ';
    }
    out << '\n';
}
