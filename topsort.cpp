// replace with copy-paste for submit
#include "graph.cpp"

class Solution {
public:
    static std::vector<int> findOrder(const int numCourses, const std::vector<std::vector<int>>& dependencies) {
        graph g;
        g.grow(numCourses);
        for(const auto &v : dependencies) {
            g.add_edge(v[1], v[0]);
        }
        auto t_sort = g.topsort();
        if(t_sort.size() != (uint)numCourses) {
            return {};
        }
        return std::vector<int>(t_sort.begin(), t_sort.end());
    }
};
