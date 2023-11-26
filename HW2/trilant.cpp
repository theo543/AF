#include <fstream>

#include "graph.cpp"

int main() {
    std::ifstream in("trilant.in");
    std::ofstream out("trilant.out");
    uint n, m, a, b, c;
    in >> n >> m >> a >> b >> c;
    graph g;
    g.grow(n);
    for(uint x = 0;x < m;x++) {
        uint n1, n2, cost;
        in >> n1 >> n2 >> cost;
        n1--; n2--;
        g.add_edge(n1, n2, cost);
        g.add_edge(n2, n1, cost);
    }
    const auto dist_a = g.dijkstra(a - 1);
    const auto dist_b = g.dijkstra(b - 1);
    const auto dist_c = g.dijkstra(c - 1);
    uint best_trilant = UINT64_MAX;
    uint best_trilant_node = 0;
    for(uint x = 0;x < n;x++) {
        uint trilant = dist_a.distances.at(x) + dist_b.distances.at(x) + dist_c.distances.at(x);
        if(trilant < best_trilant) {
            best_trilant = trilant;
            best_trilant_node = x;
        }
    }
    out << best_trilant << '\n';
    const auto print_reconstructed_path = [&](const auto &dist) {
        const auto path = dist.reconstruct_path(best_trilant_node, false);
        out << path.size() << ' ';
        for(const auto &node : path) {
            out << node + 1 << ' ';
        }
        out << '\n';
    };
    print_reconstructed_path(dist_a);
    print_reconstructed_path(dist_b);
    print_reconstructed_path(dist_c);
}
