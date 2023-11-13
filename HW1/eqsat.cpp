#include "graph.cpp"
#include <string>

class Solution {
public:
    static bool equationsPossible(const std::vector<std::string>& equations) {
        // format of equations: [a-z][!=]=[a-z]
        struct eq {
            uint a, b;
        };
        std::vector<eq> equality_eqs, inequality_eqs;
        for(const auto &e : equations) {
            eq eq;
            eq.a = e[0] - 'a';
            eq.b = e[3] - 'a';
            if(e[1] == '=') {
                equality_eqs.push_back(eq);
            } else {
                inequality_eqs.push_back(eq);
            }
        }

        // use a graph to find connected components of equality
        graph g;
        g.grow(26);
        for(const auto &e : equality_eqs) {
            g.add_edge(e.a, e.b);
            g.add_edge(e.b, e.a);
        }
        auto comp = g.components();

        // check for contradictions
        for(const auto &e : inequality_eqs) {
            if(comp[e.a] == comp[e.b]) {
                return false;
            }
        }

        return true;
    }
};
