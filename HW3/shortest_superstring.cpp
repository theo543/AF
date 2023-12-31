#include <vector>
#include <string>

#include "graph.cpp"

class Solution {
public:
    static std::string find_shortest_combination(const std::string &a, const std::string &b) {
        std::string result = b;
        for(uint start = 0; start < a.size(); start++) {
            uint suffix_size = a.size() - start;
            if(suffix_size > b.size()) {
                continue;
            }
            for(uint i = 0;i < suffix_size;i++) {
                if(a[start + i] != b[i]) {
                    goto continue_outer;
                }
            }
            assert(suffix_size != 0);
            result = "";
            result.append(b.begin() + suffix_size, b.end());
            break;
            continue_outer:;
        }
        return result;
    }
    static std::string shortestSuperstring(const std::vector<std::string>& words) {
        graph g;
        std::vector<std::vector<std::string>> combinations(words.size(), std::vector<std::string>(words.size()));
        g.grow(words.size() + 1);
        const uint dummy_node = words.size();
        for(uint x = 0;x < words.size();x++) {
            g.add_edge(dummy_node, x, words[x].size());
            g.add_edge(x, dummy_node, 0);
            for(uint y = 0;y < words.size();y++) {
                const auto &comb = find_shortest_combination(words[x], words[y]);
                combinations[x][y] = comb;
                g.add_edge(x, y, comb.size());
                //printf("Cost of %llu (%s) to %llu (%s): %llu (%s)\n", x, words[x].c_str(), y, words[y].c_str(), comb.size(), comb.c_str());
            }
        }
        const auto &path = g.traveling_salesman().second;
        std::string result = words[path[1]];
        for(uint x = 1;x < (path.size() - 2);x++) {
            result += combinations[path[x]][path[x + 1]];
        }
        return result;
    }
};
