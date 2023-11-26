#include <iostream>
#include "cheapest_flight_within_k_stops.cpp"
using std::vector;

void run_test(int n, vector<vector<int>> flights, int src, int dst, int k) {
    std::cout << "\nRunning test:\n";
    for(const auto &v : flights) {
        std::cout << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
    }
    std::cout << "Result: " << Solution::findCheapestPrice(n, flights, src, dst, k) << '\n';
}

int main() {
    run_test(4, {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}}, 0, 3, 1);
    run_test(3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 1);
    run_test(3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 0);
    run_test(5, {{4, 1, 1}, {1, 2, 3}, {0, 3, 2}, {0, 4, 10}, {3, 1, 1}, {1, 4, 3}}, 2, 1, 1);
    run_test(5, {{0, 1, 1}, {0, 2, 5}, {1, 2, 1}, {2, 3, 1}}, 0, 3, 1);
}
