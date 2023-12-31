#include <iostream>

#include "shortest_path_all_nodes.cpp"

int main() {
    std::vector<std::vector<int>> graph = {{1, 2, 3}, {0}, {0}, {0}};
    std::cout << "Expected answer: 4\n";
    int answer = Solution::shortestPathLength(graph);
    std::cout << "Answer: " << answer << '\n';
    std::cout << "Expected answer: 0\n";
    graph = {{}};
    answer = Solution::shortestPathLength(graph);
    std::cout << "Answer: " << answer << '\n';
    graph = {{5,9},{9},{5},{4,5},{3,6,7},{3,0,2},{4,8},{4},{6},{0,1}};
    std::cout << "Expected answer: 11\n";
    answer = Solution::shortestPathLength(graph);
    std::cout << "Answer: " << answer << '\n';
}
