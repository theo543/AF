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
    std::vector<int> patrols_on_node(nr_nodes, 0);

    const auto all_patrols_returned = [&]() {
        for(const auto &p : patrols_data) {
            if(p.current_node != 0) {
                return false;
            }
        }
        return true;
    };

    const auto advance_patrols = [](std::vector<patrol> &pd, std::vector<int> &pon) {
        for(auto &p : pd) {
            pon[p.nodes[p.current_node]]--;
            p.current_node = (p.current_node + 1) % p.nodes.size();
            pon[p.nodes[p.current_node]]++;
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
        patrols_on_node[patrols_data[x].nodes[0]]++;
    }

    std::vector<patrol> patrols_data_future = patrols_data;
    std::vector<int> patrols_on_node_future = patrols_on_node;

    advance_patrols(patrols_data_future, patrols_on_node_future);

    graph g;
    g.grow(nr_nodes * total_copies);
    for(int copy = 0;copy < total_copies;copy++) {
        assert(copy == 0 || !all_patrols_returned());
        int dst_copy = (copy + 1) % total_copies;
        int src_offset = copy * nr_nodes;
        int dst_offset = dst_copy * nr_nodes;
        const auto add_if_safe = [&](int a, int b) {
            if(patrols_on_node_future[b] > 0) {
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
        advance_patrols(patrols_data_future, patrols_on_node_future);
        advance_patrols(patrols_data, patrols_on_node);
    }
    assert(all_patrols_returned());
    auto bfs = g.bfs_distances({0});
    uint shortest = UINT32_MAX;
    for(const auto &b : bfs) {
        if((b.node % nr_nodes) == (nr_nodes - 1)) {
            shortest = std::min(shortest, b.distance);
        }
    }
    cout << shortest << '\n';
    cout.flush();
}
