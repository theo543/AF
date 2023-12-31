#include <iostream>
#include <vector>
#include <string>

#include "reconstruct_itinerary.cpp"

int main() {
    std::vector<std::vector<std::string>> input = {{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
    std::vector<std::string> answer = Solution::findItinerary(input);
    std::cout << "Expected answer: JFK MUC LHR SFO SJC\n";
    std::cout << "Answer: ";
    for(const auto &s : answer) {
        std::cout << s << ' ';
    }
    std::cout << '\n';

    input = {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}};
    answer = Solution::findItinerary(input);
    std::cout << "Expected answer: JFK ATL JFK SFO ATL SFO\n";
    std::cout << "Answer: ";
    for(const auto &s : answer) {
        std::cout << s << ' ';
    }
    std::cout << '\n';
}
