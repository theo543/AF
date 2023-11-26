#include <fstream>
#include <algorithm>
#include <numeric>
#include "graph.cpp"

int main() {
    std::ifstream in("oracol.in");
    std::ofstream out("oracol.out");
    uint n;
    in >> n;
    graph g;
    // node X represents the sum from 0 to X - 1
    // so node 1 is 0, node 2 is 0..1, node 3 is 0..2, etc.
    // node 0 represents a constant
    // we want a MST to reduce everything to a constant
    // knowing all partial sums <=> knowing the numbers
    g.grow(n + 1);
    for(uint from = 0;from < n;from++) {
        for(uint to = from;to < n;to++) {
            uint c;
            in >> c;
            g.add_edge(from, to + 1, c);
        }
    }
    const auto mst = g.mst();
    uint sum = std::accumulate(mst.begin(), mst.end(), 0, [](uint a, const edge &e) { return a + e.cost; });
    out << sum << '\n';
}
