#include <iostream>

#include "graph.cpp"

bool verify_correctness(const std::vector<uint> &amounts, const std::vector<uint> &targets, const std::vector<std::vector<uint>> &output) {
    std::vector<uint> final_amt = amounts;
    std::vector<uint> final_tgt(targets.size(), 0);
    for(uint x = 0;x < output.size();x++) {
        for(uint y = 0;y < output.size();y++) {
            final_amt[x] -= output[x][y];
            final_tgt[y] += output[x][y];
        }
    }
    for(uint x = 0;x < targets.size();x++) {
        if((final_amt[x] != 0) || (final_tgt[x] != targets[x])) {
            return false;
        }
    }
    return true;
}

int main() {
    uint n, m;
    std::cin >> n >> m;
    graph g;
    g.grow(n * 2 + 2);
    const uint source = n * 2, sink = n * 2 + 1;
    std::vector<uint> amounts(n), targets(n);
    uint target_total = 0;
    for(uint x = 0;x < n;x++) {
        std::cin >> amounts[x];
        g.add_edge(source, x, amounts[x]);
        g.add_edge(x, x + n, amounts[x]);
    }
    for(uint x = 0;x < n;x++) {
        std::cin >> targets[x];
        target_total += targets[x];
        g.add_edge(n + x, sink, targets[x]);
    }
    for(uint x = 0, a, b;x < m;x++) {
        std::cin >> a >> b; a--; b--;
        g.add_edge(a, n + b, amounts[a]);
        g.add_edge(b, n + a, amounts[b]);
    }
    const auto flow = g.edmonds_karp(source, sink);
    if(flow.total != target_total) {
        std::cout << "NO\n";
        return 0;
    }
    std::vector<std::vector<uint>> output = std::vector<std::vector<uint>>(n, std::vector<uint>(n, 0));
    for(const auto &node : flow.edges) {
        for(const auto &edge : node) {
            if(edge.flow != 0 && edge.src != source && edge.dst != sink) {
                assert(edge.src < n);
                assert(edge.dst >= n);
                output[edge.src][edge.dst - n] = edge.flow;
            }
        }
    }
    if(!verify_correctness(amounts, targets, output)) {
        std::cout << "NO\n";
        return 0;
    }
    std::cout << "YES\n";
    for(uint x = 0;x < n;x++) {
        for(uint y = 0;y < n;y++) {
            std::cout << output[x][y] << ' ';
        }
        std::cout << '\n';
    }
}
