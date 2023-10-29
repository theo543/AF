#include <iostream>
#include "safe_nodes.cpp"

void run_test(const std::vector<std::vector<int>> &graph) {
    std::cout << "\nRunning test:\n";
    for(uint x = 0;x < graph.size();x++) {
        std::cout << x << ": ";
        for(auto y : graph[x]) {
            std::cout << y << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Result:\n";
    const auto r = Solution::eventualSafeNodes(graph);
    for(int x : r) {
        std::cout << x << ' ';
    }
}

int main() {
    std::vector<std::vector<int>> graph1 = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}},
                                  graph2 = {{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}};
    run_test(graph1);
    run_test(graph2);
}
