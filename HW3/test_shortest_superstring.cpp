#include <iostream>

#include "shortest_superstring.cpp"

int main() {
    std::vector<std::string> input = {"alex","loves","leetcode"};
    std::cout << "Expected size: 17" << std::endl;
    std::string answer = Solution::shortestSuperstring(input);
    std::cout << "Answer: " << answer << ' ' << answer.size() << std::endl;
    input = {"catg","ctaagt","gcta","ttca","atgcatc"};
    std::cout << "Expected size: 16" << std::endl;
    answer = Solution::shortestSuperstring(input);
    std::cout << "Answer: " << answer << ' ' << answer.size() << std::endl;
    input = {"sssv","svq","dskss","sksss"};
    std::cout << "Expected size: 8" << std::endl;
    answer = Solution::shortestSuperstring(input);
    std::cout << "Answer: " << answer << ' ' << answer.size() << std::endl;
}
