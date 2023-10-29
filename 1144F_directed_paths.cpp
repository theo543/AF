#include "graph.cpp"
#include <iostream>

int main() {
    int n, m;
    std::cin >> n >> m;
    graph g;
    g.grow(n);
    std::vector<int> src(m), dst(m);
    for(int i = 0;i < m;i++) {
        int a, b;
        std::cin >> a >> b;
        a--; b--;
        // remember the edges, since output requires same order as input
        src[i] = a;
        dst[i] = b;
        g.add_edge(a, b);
        g.add_edge(b, a);
    }
    auto bipartite_result = g.bipartition();
    if(!bipartite_result.first) {
        // not bipartite <=> odd cycle => directed path of length at least 2 => no solution
        std::cout << "NO\n";
        return 0;
    }
    auto bip = bipartite_result.second;
    std::cout << "YES\n";
    // just make the edges go from part 0 to part 1
    for(int i = 0;i < m;i++) {
        if(bip[src[i]] == 0) {
            std::cout << 1;
        } else {
            std::cout << 0;
        }
    }
    std::cout << '\n';
}
