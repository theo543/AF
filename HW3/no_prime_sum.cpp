#include <iostream>

#include "graph.cpp"

int main() {
    std::vector<char> is_prime(200000 + 1, false);
    for(uint x = 2;x <= 200000;x++) {
        is_prime[x] = true;
        for(uint y = 2;y < std::min(uint{450}, x - 1);y++) {
            if(x % y == 0) {
                is_prime[x] = false;
                break;
            }
        }
    }

    uint n;
    std::cin >> n;
    std::vector<uint> left, right, values(n);
    std::vector<std::pair<uint, uint>> edges;
    for(uint x = 0;x < n;x++){
        std::cin >> values[x];
        if(values[x] % 2) {
            left.push_back(x);
        } else {
            right.push_back(x);
        }
    }
    for(uint l : left) {
        for(uint r : right) {
            if(is_prime[values[l] + values[r]]) {
                edges.push_back({l, r});
            }
        }
    }
    const auto &solution = solve_bipartite(left, right, edges, true);
    std::cout << solution.minimum_vertex_cover.size() << '\n';
    for(uint node : solution.minimum_vertex_cover) {
        std::cout << values[node] << ' ';
    }
    std::cout << '\n';
}
