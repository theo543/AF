#include <vector>
#include <cstdint>
#include <cassert>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <set>

#define uint uint64_t
#define sint  int64_t

#if __cplusplus >= 202002L
#define POPCOUNT std::popcount
#else
#define POPCOUNT __builtin_popcount
#endif

struct edge {
    uint src;
    uint dst;
    sint cost;
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

struct djikstra_result {
    std::vector<uint> distances;
    std::vector<uint> parents;

    std::vector<uint> reconstruct_path(uint node, bool fix_order = true) const {
        assert(node < distances.size());
        std::vector<uint> path;
        while(node != parents[node]) {
            path.push_back(node);
            node = parents[node];
        }
        path.push_back(node);
        if(fix_order) {
            std::reverse(path.begin(), path.end());
        }
        return path;
    }
};

struct union_find {
    std::vector<uint> parent;
    std::vector<uint> size;
    uint find(uint x) {
        assert(x < parent.size());
        uint answer = x;
        while(parent[answer] != answer) {
            answer = parent[answer];
        }
        uint second_pass = x;
        while(parent[second_pass] != second_pass) {
            uint next = parent[second_pass];
            parent[second_pass] = answer;
            second_pass = next;
        }
        return answer;
    }
    void merge(uint a, uint b) {
        assert(a < parent.size());
        assert(b < parent.size());
        a = find(a);
        b = find(b);
        if(a == b) {
            return;
        }
        if(size[a] < size[b]) {
            std::swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

uint get_mst_cost(const std::vector<edge> &edges) {
    return std::accumulate(edges.begin(), edges.end(), 0, [](const auto &acc, const auto &e) {
        return acc + e.cost;
    });
}

class graph {
    std::vector<node> nodes;
    bool using_union_find = false;
    union_find uf;
public:
    graph() = default;
    uint nr_nodes() const {
        return nodes.size();
    }
    void grow(uint size) {
        assert(nodes.size() <= size);
        nodes.resize(size);
    }
    edge_indexes add_edge(uint src, uint dst, sint cost = 1) {
        assert(src < nr_nodes());
        assert(dst < nr_nodes());
        nodes[dst].in.push_back({src, dst, cost});
        nodes[src].out.push_back({src, dst, cost});
        if(using_union_find) {
            uf.merge(src, dst);
        }
        return {src, dst, static_cast<uint32_t>(nodes[dst].in.size() - 1), static_cast<uint32_t>(nodes[src].out.size() - 1)};
    }
    void set_cost(const edge_indexes &e, sint cost) {
        assert(e.src < nr_nodes());
        assert(e.dst < nr_nodes());
        assert(e.in_index < nodes[e.dst].in.size());
        assert(e.out_index < nodes[e.src].out.size());
        nodes[e.dst].in[e.in_index].cost = cost;
        nodes[e.src].out[e.out_index].cost = cost;
    }
    uint get_cost(const edge_indexes &e) {
        assert(e.src < nr_nodes());
        assert(e.dst < nr_nodes());
        assert(e.in_index < nodes[e.dst].in.size());
        assert(e.out_index < nodes[e.src].out.size());
        assert(nodes[e.dst].in[e.in_index].cost == nodes[e.src].out[e.out_index].cost);
        return nodes[e.dst].in[e.in_index].cost;
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
                for(const auto &e : nodes[next_node].out) {
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
            for(const auto &e : nodes[node].out) {
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
            for(const auto &e : nodes[bfs[x].node].out) {
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
        std::vector<uint> comp(sz, UINT64_MAX);
        uint next_comp = 0;
        for(uint x = 0;x < sz;x++) {
            if(comp[x] == UINT64_MAX) {
                auto bfs_result = bfs_distances({x});
                for(auto r : bfs_result) {
                    comp[r.node] = next_comp;
                }
            }
            next_comp++;
        }
        for(uint x = 0;x < sz;x++) {
            assert(comp[x] != UINT64_MAX);
        }
        return comp;
    }

    struct node_w_dfs_result {
        uint open; // time we discovered this node
        uint close; // node with lowest open time that we can reach from this node
    };

    // DFS to find open and close times for each node, UINT64_MAX if unreachable, single source
    std::vector<node_w_dfs_result> dfs_open_close(uint root) {
        uint sz = nr_nodes();
        assert(root < sz);

        std::vector<node_w_dfs_result> result(sz, {UINT64_MAX, UINT64_MAX});
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
            assert(open(node) == UINT64_MAX);
            assert(close(node) == UINT64_MAX);
            open(node) = close(node) = next_open++;
            call_stack.push({node, parent, 0});
        };

        call(root, UINT64_MAX);

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
            } else if(open(child) == UINT64_MAX) {
                call(child, node);
                continue; // recurse
            } else {
                close(node) = std::min(close(node), open(child));
                continue; // continue to next iteration
            }
        }

        return result;
    }

    djikstra_result dijkstra(uint root) {
        uint sz = nr_nodes();
        assert(root < sz);

        std::vector<uint> distances(sz, UINT64_MAX);
        std::vector<uint> parents(sz, UINT64_MAX);
        std::vector<bool> visited(sz, false);

        struct lazy_dji_node {
            uint node;
            uint distance;

            bool operator<(const lazy_dji_node &other) const {
                // priority queue is a max heap, so we want to return true if this distance is smaller
                return distance > other.distance;
            }
        };

        std::priority_queue<lazy_dji_node> pq;
        distances[root] = 0;
        parents[root] = root;
        pq.push({root, 0});

        while(!pq.empty()) {
            auto top = pq.top();
            // once a node is visited never look at it again (assume no negative edges)
            visited[top.node] = true;
            pq.pop();
            if(top.distance != distances[top.node]) {
                // we've already found a shorter path to this node
                // lazy djikstra does not use a decrease-key operation, so ignore instead
                continue;
            }
            for(const auto &e : nodes[top.node].out) {
                assert(e.cost >= 0);
                uint relaxed_distance = top.distance + e.cost;
                if(relaxed_distance < distances[e.dst]) {
                    distances[e.dst] = relaxed_distance;
                    parents[e.dst] = top.node;
                    pq.push({e.dst, relaxed_distance});
                }
            }
        }
        return {distances, parents};
    }

    void init_union_find() {
        uint sz = nr_nodes();
        uf.size = std::vector<uint>(sz, 1);
        uf.parent.resize(sz);
        for(uint x = 0;x < sz;x++) {
            uf.parent[x] = x;
        }
        using_union_find = true;
    }

    uint find(uint x) {
        assert(x < nr_nodes());
        assert(using_union_find);
        return uf.find(x);
    }

    uint find_size(uint x) {
        assert(x < nr_nodes());
        assert(using_union_find);
        return uf.size[uf.find(x)];
    }

    std::vector<edge> mst() {
        union_find mst_uf{std::vector<uint>(nr_nodes()), std::vector<uint>(nr_nodes(), 1)};
        for(uint x = 0;x < nr_nodes();x++) {
            mst_uf.parent[x] = x;
        }
        std::vector<edge> edges;
        for(uint x = 0;x < nr_nodes();x++) {
            edges.insert(edges.end(), nodes[x].out.begin(), nodes[x].out.end());
        }
        std::sort(edges.begin(), edges.end(), [](const edge &a, const edge &b) {
            return a.cost < b.cost;
        });
        std::vector<edge> mst;
        for(const auto &e : edges) {
            if(mst_uf.find(e.src) != mst_uf.find(e.dst)) {
                mst_uf.merge(e.src, e.dst);
                mst.push_back(e);
            }
        }
        return mst;
    }

    struct flow_edge {
        uint src;
        uint dst;
        sint flow;
        sint capacity;
    };

    struct flow_result {
        uint total;
        std::vector<std::vector<flow_edge>> edges;
    };

    flow_result edmonds_karp(uint src, uint dst) {
        flow_result flow{0, {}};

        std::vector<std::vector<flow_edge*>> back_edges;

        flow.edges.resize(nodes.size());
        back_edges.resize(nodes.size());
        for(uint x = 0;x<nodes.size();x++) {
            flow.edges[x].resize(nodes[x].out.size());
            for(uint y = 0;y<nodes[x].out.size();y++) {
                const auto &edge = nodes[x].out[y];
                flow.edges[x][y] = flow_edge{edge.src, edge.dst, 0, edge.cost};
                back_edges[edge.dst].push_back(&flow.edges[x][y]);
            }
        }

        struct flow_bfs_step {
            uint node;
            uint prev_step;
            flow_edge *via;
            bool is_back_edge;
        };

        std::vector<flow_bfs_step> bfs;
        std::vector<char> visited(flow.edges.size());

        // loop until BFS fails
        for(;;) {
            // try to find a path
            bfs.clear();
            std::fill(visited.begin(), visited.end(), false);
            bfs.push_back({src, 0, nullptr, false});
            for(uint i = 0;i<bfs.size();i++) {
                uint node = bfs[i].node;
                // check forward edges
                auto &out_edges = flow.edges[node];
                for(flow_edge &edge : out_edges) {
                    if(edge.flow == edge.capacity || visited[edge.dst]) {
                        continue;
                    }
                    visited[edge.dst] = true;
                    bfs.push_back({edge.dst, i, &edge, false});
                    // check if we found a path
                    if(bfs.back().node == dst) {
                        goto break_outer__path_found;
                    }
                }
                // check backward edges
                const auto &in_edges = back_edges[node];
                for(uint j = 0;j<in_edges.size();j++) {
                    flow_edge &edge = *in_edges[j];
                    if(edge.flow == 0 || visited[edge.src]) {
                        continue;
                    }
                    visited[edge.src] = true;
                    bfs.push_back({edge.src, i, &edge, true});
                    // check if we found a path
                    if(bfs.back().node == dst) {
                        goto break_outer__path_found;
                    }
                }
            }
            break;
            break_outer__path_found:
            // trace path, perform updates
            sint flow_increase = INT64_MAX;
            for(uint last_step = bfs.size() - 1;last_step != 0;last_step = bfs[last_step].prev_step) {
                const auto &edge = *bfs[last_step].via;
                if(bfs[last_step].is_back_edge) {
                    flow_increase = std::min(flow_increase, edge.flow);
                } else {
                    flow_increase = std::min(flow_increase, edge.capacity - edge.flow);
                }
            }
            assert(flow_increase > 0);
            for(uint last_step = bfs.size() - 1;last_step != 0;last_step = bfs[last_step].prev_step) {
                auto &edge = *bfs[last_step].via;
                if(bfs[last_step].is_back_edge) {
                    assert(flow_increase <= edge.flow);
                    edge.flow -= flow_increase;
                } else {
                    assert(flow_increase <= (edge.capacity - edge.flow));
                    edge.flow += flow_increase;
                }
            }
        }

        // calculate total flow
        for(const auto &edge : flow.edges[src]) {
            flow.total += edge.flow;
        }

        return flow;
    }

    std::pair<uint, std::vector<uint>> traveling_salesman() {
        const uint size = nodes.size();
        std::vector<uint> matrix(size * size, UINT64_MAX);
        const auto m_at = [&matrix, size](uint a, uint b) -> uint& {
            return matrix[a * size + b];
        };
        uint upper_bound = 0;
        for(const auto &node : nodes) {
            for(const auto &edge : node.out) {
                upper_bound += edge.cost;
                m_at(edge.src, edge.dst) = edge.cost;
            }
        }
        upper_bound *= 10;
        upper_bound = std::max(upper_bound, uint{UINT32_MAX});
        std::replace_if(matrix.begin(), matrix.end(), [](uint val) -> bool {return val == UINT64_MAX;}, upper_bound);
        struct dp_data {
            uint cost;
            uint node;
        };
        uint mask_size = (1 << (size - 1));
        std::vector<dp_data> dp(mask_size * size, {UINT64_MAX, UINT64_MAX});
        const auto dp_at = [&dp, size](uint mask, uint node) -> dp_data& {
            assert(node <= (size - 1));
            return dp[mask * size + node];
        };
        const auto mask_has = [size](uint mask, uint node) {
            assert(node <= (size - 1));
            return mask & (1 << node);
        };
        const auto node_to_mask = [size](uint node) {
            assert(node <= (size - 1));
            return (1 << node);
        };
        std::vector<uint> bitmasks(mask_size);
        std::iota(bitmasks.begin(), bitmasks.end(), 0);
        std::sort(bitmasks.begin(), bitmasks.end(), [](uint a, uint b){
            return POPCOUNT(a) < POPCOUNT(b);
        });
        for(uint x = 0;x < bitmasks.size();x++) {
            if(POPCOUNT(bitmasks[x]) == 2) {
                bitmasks.erase(bitmasks.begin(), bitmasks.begin() + x);
                break;
            }
        }
        if(POPCOUNT(bitmasks.back()) < 2) {
            bitmasks.clear();
        }
        for(uint node = 0;node < (size - 1);node++) {
            dp_at(node_to_mask(node), node) = {m_at(size - 1, node), node};
        }
        for(uint mask : bitmasks) {
            assert(POPCOUNT(mask) >= 2);
            for(uint to = 0; to < (size - 1);to++) {
                if(!mask_has(mask, to)) {
                    continue;
                }
                uint best = UINT64_MAX;
                uint node = UINT64_MAX;
                for(uint from = 0;from < (size - 1);from++) {
                    if((from == to) || !mask_has(mask, from)) {
                        continue;
                    }
                    uint submask = mask & ~node_to_mask(to);
                    uint cost_to_from = dp_at(submask, from).cost;
                    uint edge_to = m_at(from, to);
                    uint cost = cost_to_from + edge_to;
                    if(cost < best) {
                        best = cost;
                        node = from;
                    }
                }
                dp_at(mask, to) = {best, node};
            }
        }
        uint best_last_node = UINT64_MAX;
        uint best_last_cost = UINT64_MAX;
        uint remaining_nodes = mask_size - 1;
        for(uint last = 0; last < (size - 1); last++) {
            uint cost = dp_at(remaining_nodes, last).cost + m_at(last, size - 1);
            if(cost < best_last_cost) {
                best_last_cost = cost;
                best_last_node = last;
            }
        }
        std::pair<uint, std::vector<uint>> answer = {best_last_cost, {size - 1, best_last_node}};
        uint last_node = best_last_node;
        while(remaining_nodes != 0) {
            uint next = dp_at(remaining_nodes, last_node).node;
            assert(next != UINT64_MAX);
            remaining_nodes &= ~node_to_mask(last_node);
            answer.second.push_back(next);
            last_node = next;
        }
        answer.second.back() = size - 1;
        std::reverse(answer.second.begin(), answer.second.end());
        return answer;
    }

    /*
     * find a valid start of an eulerian path in an undirected graph
     * cycles just return 0 since any node would work
     */
    uint find_eulerian_start() {
        bool is_start_node = false;
        bool is_end_node = false;
        uint start_node = 0;
        for(uint x = 0;x < nodes.size();x++) {
            if(nodes[x].in.size() == nodes[x].out.size()) {
                continue;
            }
            if(nodes[x].in.size() + 1 == nodes[x].out.size()) {
                assert(!is_start_node);
                is_start_node = true;
                start_node = x;
            }
            if(nodes[x].in.size() == nodes[x].out.size() + 1) {
                assert(!is_end_node);
                is_end_node = true;
            }
        }
        return start_node;
    }

    /*
     * undirected probably doesn't work with duplicate edges
     */
    std::vector<uint> eulerian_path(uint start = 0, bool undirected = false) {
        const auto sort_edge = [](const edge &edge) -> std::pair<uint, uint> {
            if(edge.src > edge.dst) {
                return {edge.dst, edge.src};
            } else {
                return {edge.src, edge.dst};
            }
        };

        std::vector<uint> cycle;
        std::vector<uint> unfinished_nodes = {start};
        std::set<std::pair<uint, uint>> used_edges;
        std::vector<std::vector<edge>::iterator> next_edge(nodes.size());
        for(uint x = 0;x < nodes.size();x++) {
            next_edge[x] = nodes[x].out.begin();
        }
        while(!unfinished_nodes.empty()) {
            uint node = unfinished_nodes.back();
            if(undirected) {
                while(next_edge[node] != nodes[node].out.end() && used_edges.find(sort_edge(*next_edge[node])) != used_edges.end()) {
                    next_edge[node]++;
                }
            }
            if(next_edge[node] == nodes[node].out.end()) {
                cycle.push_back(node);
                unfinished_nodes.pop_back();
            } else {
                if(undirected) {
                    used_edges.insert(sort_edge(*next_edge[node]));
                }
                unfinished_nodes.push_back(next_edge[node]->dst);
                next_edge[node]++;
            }
        }
        std::reverse(cycle.begin(), cycle.end());
        return cycle;
    }
};

struct bipartite_info {
    std::vector<std::pair<uint, uint>> maximum_matching;
    std::vector<uint> minimum_vertex_cover;
};

bipartite_info solve_bipartite(const std::vector<uint> &left, const std::vector<uint> &right, const std::vector<std::pair<uint, uint>> &edges, bool include_min_vertex_cover) {
    graph g;
    const auto nodes = left.size() + right.size();
    g.grow(nodes + 2);
    for(uint l : left) {
        g.add_edge(nodes, l, 1);
    }
    for(uint r : right) {
        g.add_edge(r, nodes + 1, 1);
    }
    for(const auto &edge : edges) {
        g.add_edge(edge.first, edge.second, 1);
    }
    const auto flow = g.edmonds_karp(nodes, nodes + 1);
    bipartite_info result;
    std::vector<char> left_is_matched(nodes, false);
    for(const auto &node : flow.edges) {
        for(const auto &edge : node) {
            if(edge.src != nodes && edge.dst != nodes + 1 && edge.flow == 1) {
                result.maximum_matching.push_back({edge.src, edge.dst});
                left_is_matched.at(edge.src) = true;
            }
        }
    }
    if(include_min_vertex_cover) {
        // Kőnig's theorem
        // https://math.stackexchange.com/a/3044297
        std::vector<uint> unmatched_left_nodes;
        for(uint node : left) {
            if(!left_is_matched[node]) {
                unmatched_left_nodes.push_back(node);
            }
        }
        for(const auto &edge : result.maximum_matching) {
            g.add_edge(edge.second, edge.first);
        }
        const auto &bfs = g.bfs_distances(unmatched_left_nodes);
        std::vector<char> in_answer(nodes, false);
        for(uint node : left) {
            in_answer[node] = true;
        }
        for(const auto &node_ : bfs) {
            uint node = node_.node;
            if(node >= nodes) {
                continue;
            }
            in_answer[node] = !in_answer[node];
        }
        for(uint i = 0;i < nodes;i++) {
            if(in_answer[i]) {
                result.minimum_vertex_cover.push_back(i);
            }
        }
        assert(result.maximum_matching.size() == result.minimum_vertex_cover.size());
    }
    return result;
}
