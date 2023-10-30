#include <fstream>
#include <vector>

std::ifstream in("patrol2.in");
std::ofstream out("patrol2.out");

int n, m, k;

// lcm(1,2,3,4,5,6,7) = 420
// first subtask: 420 * 100 ~= 500 * 100 = 50000 = 5 * 10^4
// second subtask: 1 * 10000 = 10^4
// third subtask: 2 * 10^4
const int MAX_BOOLS = 5 * 10000;

std::vector<bool> is_occupied(MAX_BOOLS, false), is_visited(MAX_BOOLS, false);

const int MAX_NODES = 10000;

// at most 5 * 10^4 edges... even with the overhead of a vector<vector<int>>, should be fine
std::vector<std::vector<int>> edges(MAX_NODES);

int main() {
    in >> n >> m >> k;
    for(int x = 0, a, b;x < m;x++) {
        in >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    for(int x = 0;x < n;x++) {
        edges[x].push_back(x);
    }
    int num_repeats;
    if(k == 0) {
        // second subtask
        num_repeats = 1;
    } else if(n <= 100) {
        // first or third
        num_repeats = 420;
    } else {
        // definitely third subtask
        num_repeats = 2;
    }
    std::vector<int> patrol(7);
    for(int x = 0, li;x < k;x++) {
        in >> li;
        for(int y = 0;y < li;y++) {
            in >> patrol[y];
        }
        if((num_repeats == 2) && (li > 2)) {
            __builtin_trap();
        }
        for(int time = 0;time < num_repeats;time++) {
            int current_patrol = time % li;
            int occupied_node = patrol[current_patrol];
            is_occupied[(time * n) + occupied_node] = true;
        }
    }

    struct bfs_info {
        int next_time; // for convenience store NEXT time, not CURRENT time
        int node;
        int distance;
    };

    std::vector<bfs_info> bfs;

    bfs.reserve(num_repeats * n);
    bfs.push_back({1, 0, 0});
    is_visited[0] = true;
    for(std::size_t x = 0;x < bfs.size();x++) {
        bfs_info b = bfs[x];
        for(const int dest : edges[b.node]) {
            int bool_index = (b.next_time * n) + dest;
            if(is_occupied[bool_index] || is_visited[bool_index]) {
                continue;
            }
            if(dest == (n - 1)) {
                // shortest path found
                out << b.distance + 1 << '\n';
                return 0;
            }
            is_visited[bool_index] = true;
            bfs.push_back({(b.next_time + 1) % num_repeats, dest, b.distance + 1});
        }
    }
    out << "-1" << '\n';
}
