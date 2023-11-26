#include "graph.cpp"

using std::vector;

class Solution {
public:
    static vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, const vector<vector<int>>& edges) {
        std::vector<edge_indexes> ei(edges.size());
        graph g;
        g.grow(n);
        for(uint x = 0;x < edges.size();x++) {
            ei[x] = g.add_edge(edges[x][0], edges[x][1], edges[x][2]);
        }
        std::vector<std::vector<int>> psuedo_critical_then_critical(2);
        uint base_cost = get_mst_cost(g.mst());
        for(uint x = 0;x < edges.size();x++) {
            uint orig_edge = g.get_cost(ei[x]);
            g.set_cost(ei[x], base_cost + 1);
            uint cost_without_edge = get_mst_cost(g.mst());
            if(cost_without_edge > base_cost) {
                psuedo_critical_then_critical[0].push_back(x);
                g.set_cost(ei[x], orig_edge);
                continue;
            }
            g.set_cost(ei[x], 0);
            uint cost_with_edge_guaranteed = get_mst_cost(g.mst()) + orig_edge;
            if(cost_with_edge_guaranteed == base_cost) {
                psuedo_critical_then_critical[1].push_back(x);
            }
            g.set_cost(ei[x], orig_edge);
        }
        return psuedo_critical_then_critical;
    }
};
