#include <numeric>
#include <fstream>
#include "graph.cpp"

int main() {
    std::ifstream in("apm2.in");
    std::ofstream out("apm2.out");
    uint n, m, q;
    in >> n >> m >> q;
    graph base;
    base.grow(n);
    for(uint i = 0;i < m;i++) {
        uint from, to, cost;
        in >> from >> to >> cost;
        base.add_edge(from - 1, to - 1, cost);
    }
    uint total_base_cost;
    {
        const auto mst = base.mst();
        total_base_cost = std::accumulate(mst.begin(), mst.end(), 0, [](uint a, const edge &e) { return a + e.cost; });
    }
    for(uint i = 0;i < q;i++) {
        graph g = base;
        edge_indexes edge;
        {
            uint from, to;
            in >> from >> to;
            edge = g.add_edge(from - 1, to - 1, 0);
        }
        uint l = 0, r = total_base_cost;
        while(l != r) {
            uint mid = (l + r + 1) / 2;
            g.set_cost(edge, mid);
            const auto mst = g.mst();
            uint total_cost = std::accumulate(mst.begin(), mst.end(), 0, [](uint a, const struct edge &e) { return a + e.cost; });
            if(total_cost < total_base_cost) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        out << l << '\n';
    }
}
