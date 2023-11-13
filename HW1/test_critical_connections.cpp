#include <iostream>
#include "critical_connections.cpp"

void run_test(const int n, const std::vector<std::vector<int>> &connections) {
    std::cout << "\nRunning test:\n";
    for(const auto &v : connections) {
        std::cout << v[0] << ' ' << v[1] << '\n';
    }
    std::cout << "Result:\n";
    const auto r = Solution::criticalConnections(n, connections);
    for(const auto &v : r) {
        std::cout << v[0] << ' ' << v[1] << '\n';
    }
}

int main() {
    run_test(4, {{0, 1}, {1, 2}, {2, 0}, {1, 3}});
    run_test(2, {{0, 1}});
}
