#include "graph.cpp"
#include <iostream>

void solve_one_case() {
    int n, k;
    std::cin >> n >> k;
    std::vector<bool> is_marked(n);
    std::vector<int> marked_nodes;
    // read marked nodes
    for(int x = 0;x < k;x++) {
        int v;
        std::cin >> v;
        v--;
        is_marked[v] = true;
        marked_nodes.push_back(v);
    }
    // read n - 1 edges
    graph g;
    g.grow(n);
    for(int x = 0;x < n - 1;x++) {
        int a, b;
        std::cin >> a >> b;
        a--; b--;
        g.add_edge(a, b);
        g.add_edge(b, a);
    }
    // find the diameter using the two-BFS method
    // except that we only consider marked nodes
    if(k == 1) {
        // special case
        std::cout << "0\n";
        return;
    }
    auto bfs_1 = g.bfs_distances({(uint)marked_nodes[0]});
    uint max_dist = 0;
    uint max_dist_node = UINT32_MAX;
    for(const auto &b : bfs_1) {
        if(!is_marked[b.node]) {
            continue;
        }
        if(b.distance > max_dist) {
            max_dist = b.distance;
            max_dist_node = b.node;
        }
    }
    assert(max_dist_node != UINT32_MAX);
    auto bfs_2 = g.bfs_distances({max_dist_node});
    max_dist = 0;
    max_dist_node = UINT32_MAX;
    for(const auto &b : bfs_2) {
        if(!is_marked[b.node]) {
            continue;
        }
        if(b.distance > max_dist) {
            max_dist = b.distance;
            max_dist_node = b.node;
        }
    }
    assert(max_dist_node != UINT32_MAX);
    auto diameter = max_dist;
    // a node with minimum f_i should be in the middle of the diameter
    auto result = (diameter + 1) / 2;
    std::cout << result << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while(t--) {
        solve_one_case();
    }
}
