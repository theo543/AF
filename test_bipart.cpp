#include "possible_bipartition.cpp"
#include <iostream>

int main() {
    std::vector<std::vector<int>> input1 = {{1, 2}, {1, 3}, {2, 4}},
                                  input2 = {{1, 2}, {1, 3}, {2, 3}};
    std::cout << "input1: " << Solution::possibleBipartition(4, input1) << '\n';
    std::cout << "input2: " << Solution::possibleBipartition(3, input2) << '\n';
}
