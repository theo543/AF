#include <vector>
#include <cstdint>
#include <cassert>
#include <queue>
#include <stack>

#define uint uint32_t

struct edge {
    uint src;
    uint dst;
    uint cost;
};

struct edge_indexes {
    uint src;
    uint dst;
    uint in_index;
    uint out_index;
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
    edge_indexes add_edge(uint src, uint dst, uint cost = 1) {
        assert(src < nr_nodes());
        assert(dst < nr_nodes());
        nodes[dst].in.push_back({src, dst, cost});
        nodes[src].out.push_back({src, dst, cost});
        return {src, dst, static_cast<uint32_t>(nodes[dst].in.size() - 1), static_cast<uint32_t>(nodes[src].out.size() - 1)};
    }
    void set_cost(edge_indexes e, uint cost) {
        assert(e.src < nr_nodes());
        assert(e.dst < nr_nodes());
        assert(e.in_index < nodes[e.dst].in.size());
        assert(e.out_index < nodes[e.src].out.size());
        nodes[e.dst].in[e.in_index].cost = cost;
        nodes[e.src].out[e.out_index].cost = cost;
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
                // so that this works with undirected graphs, check neighbors of next_node since it may be connected
                // to a colored node
                col_vec[next_node] = A;
                for(auto e : nodes[next_node].out) {
                    if(col_vec[e.dst] == A) {
                        col_vec[e.dst] = B;
                        break;
                    }
                }
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

    struct bfs_result {
        uint node;
        uint distance;
    };

    std::vector<bfs_result> bfs_distances(const std::vector<uint> &sources) {
        uint sz = nr_nodes();
        std::vector<bfs_result> bfs;
        std::vector<char> visited(sz, false);
        for(uint x : sources) {
            assert(x < sz);
            bfs.push_back({x, 0});
            visited[x] = true;
        }
        for(uint x = 0;x < bfs.size();x++) {
            for(auto e : nodes[bfs[x].node].out) {
                if(!visited[e.dst]) {
                    visited[e.dst] = true;
                    bfs.push_back({e.dst, bfs[x].distance + 1});
                }
            }
        }
        return bfs;
    }

    std::vector<uint> components() {
        uint sz = nr_nodes();
        std::vector<uint> comp(sz, UINT32_MAX);
        uint next_comp = 0;
        for(uint x = 0;x < sz;x++) {
            if(comp[x] == UINT32_MAX) {
                auto bfs_result = bfs_distances({x});
                for(auto r : bfs_result) {
                    comp[r.node] = next_comp;
                }
            }
            next_comp++;
        }
        for(uint x = 0;x < sz;x++) {
            assert(comp[x] != UINT32_MAX);
        }
        return comp;
    }

    struct node_w_dfs_result {
        uint open; // time we discovered this node
        uint close; // node with lowest open time that we can reach from this node
    };

    // DFS to find open and close times for each node, UINT32_MAX if unreachable, single source
    std::vector<node_w_dfs_result> dfs_open_close(uint root) {
        uint sz = nr_nodes();
        assert(root < sz);

        std::vector<node_w_dfs_result> result(sz, {UINT32_MAX, UINT32_MAX});
        const auto open = [&](uint x) -> uint& {
            return result[x].open;
        };
        const auto close = [&](uint x) -> uint& {
            return result[x].close;
        };

        struct stack_frame {
            uint node;
            uint parent;
            uint next_child;
        };
        // allocate the stack on the heap to avoid stack overflow
        std::stack<stack_frame> call_stack;
        uint next_open = 0;

        const auto call = [&](uint node, uint parent) {
            assert(open(node) == UINT32_MAX);
            assert(close(node) == UINT32_MAX);
            open(node) = close(node) = next_open++;
            call_stack.push({node, parent, 0});
        };

        call(root, UINT32_MAX);

        while(!call_stack.empty()) {
            uint node = call_stack.top().node;
            uint child_index = call_stack.top().next_child;
            assert(child_index <= nodes[node].out.size());

            if(child_index == nodes[node].out.size()) {
                // end of this call
                call_stack.pop();
                if(!call_stack.empty()) {
                    // update parent's close time
                    uint parent = call_stack.top().node;
                    close(parent) = std::min(close(parent), close(node));
                }
                continue; // return from this call
            }

            uint child = nodes[node].out[child_index].dst;
            call_stack.top().next_child++; // update index for next iteration

            if(child == call_stack.top().parent) {
                continue; // continue to next iteration
            } else if(open(child) == UINT32_MAX) {
                call(child, node);
                continue; // recurse
            } else {
                close(node) = std::min(close(node), open(child));
                continue; // continue to next iteration
            }
        }

        return result;
    }
};
