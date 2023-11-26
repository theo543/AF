#include <fstream>

#include "graph.cpp"

int main() {
    std::ifstream in("camionas.in");
    std::ofstream out("camionas.out");
    uint n, m, g;
    in >> n >> m >> g;
    graph gr;
    gr.grow(n);
    for(uint x = 0;x < m;x++) {
        uint a, b, c;
        in >> a >> b >> c;
        a--; b--;
        if(c < g) {
            gr.add_edge(a, b, 1);
            gr.add_edge(b, a, 1);
        } else {
            gr.add_edge(a, b, 0);
            gr.add_edge(b, a, 0);
        }
    }
    const auto res = gr.dijkstra(0);
    out << res.distances.at(n - 1) << '\n';
}
