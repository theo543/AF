#include "graph.cpp"
#include <fstream>

int gcd(int a, int b) {
    while(b != 0) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    std::ifstream cin("patrol2.in");
    assert(cin.good());
    assert(cin.is_open());
    std::ofstream cout("patrol2.out");
    uint nr_nodes, nr_edges, nr_patrols;
    cin >> nr_nodes >> nr_edges >> nr_patrols;

    std::vector<std::pair<int, int>> edge_templates;
    for(uint x = 0; x < nr_edges; x++) {
        int a, b;
        cin >> a >> b;
        edge_templates.push_back({a, b});
    }

    struct patrol {
        int current_node = 0;
        std::vector<int> nodes;
    };

    std::vector<patrol> patrols_data(nr_patrols);
    std::vector<bool> patrols_on_node(nr_nodes, 0);

    const auto advance_patrols = [](std::vector<patrol> &pd, std::vector<bool> &pon) {
        std::fill(pon.begin(), pon.end(), false);
        for(auto &p : pd) {
            p.current_node = (p.current_node + 1) % p.nodes.size();
            pon[p.nodes[p.current_node]] = true;
        }
    };

    int total_copies = 1;

    for(uint x = 0; x < nr_patrols; x++) {
        int patrol_nodes;
        cin >> patrol_nodes;
        total_copies = lcm(total_copies, patrol_nodes);
        for(int y = 0; y < patrol_nodes; y++) {
            int v;
            cin >> v;
            patrols_data[x].nodes.push_back(v);
        }
        patrols_on_node[patrols_data[x].nodes[0]] = true;
    }

    advance_patrols(patrols_data, patrols_on_node);

    graph g;
    g.grow(nr_nodes * total_copies);
    for(int copy = 0;copy < total_copies;copy++) {
        int dst_copy = (copy + 1) % total_copies;
        int src_offset = copy * nr_nodes;
        int dst_offset = dst_copy * nr_nodes;
        const auto add_if_safe = [&](int a, int b) {
            if(patrols_on_node[b]) {
                return;
            }
            g.add_edge(src_offset + a, dst_offset + b);
        };
        // add tunnels
        for(uint e = 0;e < edge_templates.size();e++) {
            int a = edge_templates[e].first;
            int b = edge_templates[e].second;
            add_if_safe(a, b);
            add_if_safe(b, a);
        }
        // add "stay in place" edges
        for(uint x = 0;x < nr_nodes;x++) {
            add_if_safe(x, x);
        }
        advance_patrols(patrols_data, patrols_on_node);
    }
    auto bfs = g.bfs_distances({0});
    uint shortest = UINT32_MAX;
    for(const auto &b : bfs) {
        if((b.node % nr_nodes) == (nr_nodes - 1)) {
            shortest = std::min(shortest, b.distance);
        }
    }
    if(shortest == UINT32_MAX) {
        cout << "-1\n";
    } else {
        cout << shortest << '\n';
    }
}
