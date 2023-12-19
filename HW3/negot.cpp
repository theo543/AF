#include <fstream>

#include "graph.cpp"

int main() {
    std::ifstream in("negot.in");
    uint n, m, k;
    in >> n >> m >> k;
    graph g;
    g.grow(n + m + 2);
    uint source = n + m, sink = n + m + 1;
    for(uint x = 0, ti;x < n;x++) {
        g.add_edge(source, x, k);
        in >> ti;
        for(uint y = 0, store;y < ti;y++) {
            in >> store;
            store--;
            g.add_edge(x, store + n, 1);
        }
    }
    for(uint x = 0;x < m;x++) {
        g.add_edge(x + n, sink, 1);
    }
    const auto flow = g.edmonds_karp(source, sink);
    std::ofstream out("negot.out");
    out << flow.total << '\n';
}
