#include "shortest_bridge.cpp"
#include <iostream>

void run_test(const std::vector<std::vector<int>> &input) {
    std::cout << "\nRunning test:\n";
    for(uint x = 0;x < input.size();x++) {
        std::cout << x << ": ";
        for(auto y : input[x]) {
            std::cout << y << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Result: " << Solution::shortestBridge(input) << '\n';
}

int main() {
    run_test({{0, 1}, {1, 0}});
    run_test({{0, 1, 0}, {0, 0, 0}, {0, 0, 1}});
    run_test({{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}});
}