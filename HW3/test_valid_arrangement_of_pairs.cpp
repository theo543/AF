#include <iostream>
#include <vector>

#include "valid_arrangement_of_pairs.cpp"

void print_vector(const std::vector<std::vector<int>> &v) {
    std::cout << "[";
    for (const auto &x: v) {
        std::cout << "[" << x[0] << ", " << x[1] << "] ";
    }
    std::cout << "]\n";
}

void run_test_case(const std::vector<std::vector<int>> &input) {
    std::cout << "\nRunning test case: ";
    print_vector(input);
    const auto answer = Solution::validArrangement(input);
    std::cout << "Answer: ";
    print_vector(answer);
}

int main() {
    run_test_case({{5, 1}, {4, 5}, {11, 9}, {9, 4}});
    run_test_case({{1, 3}, {3, 2}, {2, 1}});
    run_test_case({{1, 2}, {1, 3}, {2, 1}});
}
