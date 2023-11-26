#include "graph.cpp"
#include <algorithm>
using std::vector;

class Solution {
public:
    static vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        std::sort(edgeList.begin(), edgeList.end(), [](const auto &a, const auto &b) {
            return a[2] < b[2];
        });
        std::vector<char> answers(queries.size(), 2);
        struct query {
            char *answer;
            int from, to, limit;
        };
        std::vector<query> queries_;
        queries_.reserve(queries.size());
        for(uint i = 0;i < queries.size();i++) {
            queries_.push_back({&answers[i], queries[i][0], queries[i][1], queries[i][2]});
        }
        std::sort(queries_.begin(), queries_.end(), [](const auto &a, const auto &b) {
            return a.limit < b.limit;
        });

        uint edge_index = 0;
        graph g;
        g.grow(n);
        g.init_union_find();
        for(const auto &q : queries_) {
            while (edge_index < edgeList.size() && edgeList[edge_index][2] < q.limit) {
                g.add_edge(edgeList[edge_index][0], edgeList[edge_index][1]);
                edge_index++;
            }
            q.answer[0] = g.find(q.from) == g.find(q.to);
        }

        return std::vector<bool>(answers.begin(), answers.end());
    }
};
