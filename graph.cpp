#include <vector>
#include <cstdint>
#include <cassert>

#define uint uint32_t

struct edge {
    uint src;
    uint dst;
};

struct node {
    std::vector<edge> in, out;
};

class graph {
    std::vector<node> nodes;
public:
    graph() = default;
    uint nr_nodes() {
        return nodes.size();
    }
    void grow(uint size) {
        assert(nodes.size() <= size);
        nodes.resize(size);
    }
    void add_edge(uint src, uint dst) {
        if(src >= nr_nodes() || dst >= nr_nodes()) {
            nodes.resize(std::max(src, dst) + 1);
        }
        nodes[dst].in.push_back({src, dst});
        nodes[src].out.push_back({src, dst});
    }

    // Topologically sort the nodes so that any edge A->B means "A comes before B".
    // Any impossible nodes will not appear in the result.
    std::vector<uint> topsort() {
        uint sz = nr_nodes();
    
        // Remaining dependencies for each node.
        std::vector<uint> remaining(sz);

        // Topsort (found via BFS).
        std::vector<uint> topsort;

        for(uint x = 0; x < sz; x++) {
            remaining[x] = nodes[x].in.size();
            if(remaining[x] == 0) {
                topsort.push_back(x);
            }
        }

        for(uint bfs = 0; bfs < topsort.size(); bfs++) {
            uint node = topsort[bfs];
            for(edge e : nodes[node].out) {
                uint dst = e.dst;
                uint &rem = remaining[dst];
                if(rem != 0) {
                    rem -= 1;
                    if(rem == 0) {
                        topsort.push_back(dst);
                    }
                }
            }
        }

        return topsort;
    }
};
