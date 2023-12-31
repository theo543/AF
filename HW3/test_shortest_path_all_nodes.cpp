#include <iostream>

#include "shortest_path_all_nodes.cpp"

int main() {
    std::vector<std::vector<int>> graph = {{1, 2, 3}, {0}, {0}, {0}};
    std::cout << "Expected answer: 4\n";
    int answer = Solution::shortestPathLength(graph);
    std::cout << "Answer: " << answer << '\n';
}
