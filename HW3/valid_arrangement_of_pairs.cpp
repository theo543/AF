#include <vector>
#include <unordered_map>

#include "graph.cpp"

class Solution {
public:
    static std::vector<std::vector<int>> validArrangement(const std::vector<std::vector<int>> &pairs) {
        std::unordered_map<int, uint> normalize_id;
        std::vector<int> denormalize_id;
        std::vector<uint> nodes;
        std::vector<std::pair<uint, uint>> edges;
        const auto add_id = [&normalize_id, &denormalize_id, &nodes](uint id) {
            if(normalize_id.find(id) == normalize_id.end()) {
                uint new_id = nodes.size();
                normalize_id[id] = new_id;
                denormalize_id.push_back(id);
                nodes.push_back(new_id);
            }
        };
        for(const auto &pair : pairs) {
            add_id(pair[0]);
            add_id(pair[1]);
            edges.push_back({normalize_id.at(pair[0]), normalize_id.at(pair[1])});
        }
        graph g;
        g.grow(nodes.size());
        for(const auto &edge : edges) {
            g.add_edge(edge.first, edge.second, 1);
        }
        const auto &start = g.find_eulerian_start();
        const auto &path = g.eulerian_path(start);
        std::vector<std::vector<int>> result;
        for(uint i = 0;i < (path.size() - 1);i++) {
            result.push_back({denormalize_id.at(path[i]), denormalize_id.at(path[i + 1])});
        }
        return result;
    }
};
