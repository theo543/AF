#include <iostream>
#include "checking_existence_limited_paths.cpp"

void run_test(int n, std::vector<std::vector<int>> &&input, std::vector<std::vector<int>> &&queries, std::vector<bool> &&expected) {
    std::cout << "\nRunning test.";
    const auto r = Solution::distanceLimitedPathsExist(n, input, queries);
    if(r == expected) {
        std::cout << " Passed.\n";
    } else {
        std::cout << " Failed.\n";
        std::cout << "Expected: ";
        for(auto x : expected) {
            std::cout << x << ' ';
        }
        std::cout << "\nGot: ";
        for(auto x : r) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    run_test(3, {{0, 1, 2}, {1, 2, 4}, {2, 0, 8}, {1, 0, 16}}, {{0, 1, 2}, {0, 2, 5}}, {false, true});
    run_test(5, {{0, 1, 10}, {1, 2, 5}, {2, 3, 9}, {3, 4, 13}}, {{0, 4, 14}, {1, 4, 13}}, {true, false});
}
