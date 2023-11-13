#include "topsort.cpp"
#include <iostream>

void run_test(int n, const std::vector<std::vector<int>> &input) {
    std::cout << "\nRunning test:\n";
    for(const auto &v : input) {
        std::cout << "[" << v[0] << ", " << v[1] << "] ";
    }
    std::cout << '\n';
    std::cout << "Result:\n";
    const auto r = Solution::findOrder(n, input);
    if(r.empty()) {
        std::cout << "<impossible>\n";
    } else {
        for(int x : r) {
            std::cout << x << ' ';
        }
    }
    std::cout << '\n';
}

int main() {
    run_test(2, {{1, 0}});
    run_test(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}});
    run_test(1, {});
    run_test(5, {});
    run_test(5, {{3, 4}, {2, 3}, {0, 2}, {1, 0}});
    run_test(4, {{0, 1}, {0, 2}, {0, 3}});
    run_test(2, {{1, 0}, {0, 1}});
    run_test(5, {{3, 4}, {2, 3}, {0, 2}, {1, 2}, {3, 0}});
}
