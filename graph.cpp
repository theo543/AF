#include <vector>
#include <cstdint>
#include <cassert>
#include <queue>

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
        assert(src < nr_nodes());
        assert(dst < nr_nodes());
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

    // Returns a bipartition if possible, else {false, {}}.
    std::pair<bool, std::vector<bool>> bipartition() {
        enum coloring {
            blank,
            A,
            B
        };
        uint sz = nr_nodes();
        std::vector<coloring> col_vec(sz, blank);
        std::queue<uint> color_from;
        uint colored = 0;
        uint next_node = 0;
        while(true) {
            if(color_from.empty()) {
                // if we finished coloring AND the queue is empty, output the result
                // (if the queue isn't empty, we don't know whether the result is valid yet)
                if(colored == sz) {
                    std::vector<bool> result;
                    result.resize(sz);
                    for(uint x = 0;x < sz;x++) {
                        assert(col_vec[x] != blank);
                        result[x] = (col_vec[x] == A);
                    }
                    return {true, result};
                }

                // if the queue is empty BUT we haven't finished coloring, then
                // we must have finished col_vec one connected component
                // pick a new node to continue the BFS in a new component
                while(col_vec[next_node] != blank) {
                    next_node++;
                    assert(next_node != sz);
                }
                col_vec[next_node] = A;
                colored++;
                color_from.push(next_node);
            }
            uint node = color_from.front();
            assert(col_vec[node] != blank);
            color_from.pop();
            for(auto e : nodes[node].out) {
                if(col_vec[e.dst] == blank) {
                    col_vec[e.dst] = (col_vec[node] == A ? B : A);
                    colored++;
                    color_from.push(e.dst);
                } else if(col_vec[e.dst] == col_vec[node]) {
                    // adjacent equal colors not allowed
                    return {false, {}};
                }
            }
        }
    }
};
