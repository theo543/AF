#include <fstream>

#include "graph.cpp"

const int MAX_NODES = 100;
const int FLOW_SOURCE = MAX_NODES * 2;
const int FLOW_SINK = MAX_NODES * 2 + 1;
/*
 * 0 -> 99 | start of a path
 * 100 -> 199 | end of a path
 * 200 | flow source
 * 201 | flow sink
 */

int main() {
    std::ifstream in("harta.in");
    std::ofstream out("harta.out");

    graph g;
    g.grow(MAX_NODES * 2 + 2);

    for(uint x = 0;x < MAX_NODES;x++) {
        for(uint y = 0;y < MAX_NODES;y++) {
            if(x != y) {
                g.add_edge(x, y + MAX_NODES, 1);
            }
        }
    }

    uint n;
    in >> n;
    uint expected_flow = 0;
    for(uint x = 0, in_degree, out_degree;x < n;x++) {
        in >> in_degree >> out_degree;
        expected_flow += in_degree;
        g.add_edge(FLOW_SOURCE, x, in_degree);
        g.add_edge(x + MAX_NODES, FLOW_SINK, out_degree);
    }

    const auto flow = g.edmonds_karp(MAX_NODES * 2, MAX_NODES * 2 + 1);

    assert(flow.total == expected_flow);

    out << flow.total << '\n';

    for(const auto &node : flow.edges) {
        for(const auto &edge : node) {
            if(edge.flow != 0 && edge.src != FLOW_SOURCE && edge.dst != FLOW_SINK) {
                assert(edge.flow > 0);
                out << edge.src + 1 << ' ' << edge.dst - MAX_NODES + 1 << '\n';
            }
        }
    }

}
