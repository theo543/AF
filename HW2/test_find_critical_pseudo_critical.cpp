#include "find_critical_pseudo_critical.cpp"
#include <iostream>

void run_test(uint n, const std::vector<std::vector<int>> &edges) {
    std::cout << "\nRunning test:\n";
    for(const auto &v : edges) {
        std::cout << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
    }
    std::cout << "Result:\n";
    const auto r = Solution::findCriticalAndPseudoCriticalEdges(n, edges);
    std::cout << "Critical:\n";
    for(const auto &v : r[0]) {
        std::cout << v << ' ';
    }
    std::cout << "\nPseudo-critical:\n";
    for(const auto &v : r[1]) {
        std::cout << v << ' ';
    }
}

int main() {
    run_test(5, {{0, 1, 1}, {1, 2, 1}, {2, 3, 2}, {0, 3, 2}, {0, 4, 3}, {3, 4, 3}, {1, 4, 6}});
    run_test(4, {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {0, 3, 1}});
    return 0;
}
