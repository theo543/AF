#include <numeric>
#include <fstream>
#include "graph.cpp"

// apm2, for an efficient solution, can't really use a black-box Krukal algorithm
// we need to be able to look at the edges as they're added to figure out where we could insert the new edge
// we need a custom Kruskal which tracks when the edge could be inserted
// else we're forced to binary search, and the time limit is too strict for an extra log factor
// I did still use the union-find, and edge struct from the graph.cpp file

// I'll still send the amp2.cpp file which does use the black-box Kruskal, but it only gets 20/100 points, then TLE
int main() {
    std::ifstream in("apm2.in");
    std::ofstream out("apm2.out");
    uint n, m, q;
    in >> n >> m >> q;
    std::vector<edge> base_edges;
    for(uint i = 0;i < m;i++) {
        uint from, to;
        sint cost;
        in >> from >> to >> cost;
        base_edges.push_back({from - 1, to - 1, cost});
    }

    std::sort(base_edges.begin(), base_edges.end(), [](const edge &a, const edge &b) { return a.cost < b.cost; });

    union_find base_uf{std::vector<uint>(n + 1), std::vector<uint>(n + 1, 1)};
    for(uint i = 0;i < n;i++) {
        base_uf.parent[i] = i;
    }

    for(uint i = 0;i < q;i++) {
        uint from, to;
        in >> from >> to;
        from--; to--;
        union_find uf = base_uf;
        sint current_cost = 0;
        bool broke_out = false;
        for(uint x = 0;x < m;x++) {
            if(current_cost != base_edges[x].cost || x == m - 1) {
                // since the edge has to appear in ALL mst, we have to assume it is the last edge in this group
                // can it still appear?
                if(uf.find(from) == uf.find(to)) {
                    broke_out = true;
                    break;
                }
                current_cost = base_edges[x].cost;
            }
            if(uf.find(base_edges[x].src) != uf.find(base_edges[x].dst)) {
                uf.merge(base_edges[x].src, base_edges[x].dst);
            }
        }
        if(!broke_out) {
            current_cost = base_edges[m - 1].cost;
        }
        out << current_cost - 1 << '\n';
    }
}
