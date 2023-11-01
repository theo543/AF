#include <fstream>
#include <cstdint>
#include <vector>

// signed 16 bits
#define s16 int16_t

struct coords {
    s16 x;
    s16 y;
    bool operator==(const coords &other) {
        return x == other.x && y == other.y;
    }
    bool operator!=(const coords &other) {
        return !(operator==(other));
    }
};

struct union_find_node {
    coords parent;
    s16 size;
    char type;
};

union_find_node uf[1000][1000];

// Access uf by coords struct.
union_find_node &ufc(coords c) {
    return uf[c.x][c.y];
}

coords union_find(coords node) {
    // Find which set the node is in.
    coords set = node;
    while(ufc(set).parent != set) {
        set = ufc(set).parent;
    }
    // Traverse again to compress path.
    coords again = node;
    while(ufc(again).parent != again) {
        coords tmp = ufc(again).parent;
        ufc(again).parent = set;
        
    }
    return set;
}

void union_merge(coords a, coords b) {
    a = union_find(a);
    b = union_find(b);

    if(a == b) {
        return;
    }

    if(ufc(a).size < ufc(b).size) {
        std::swap(a, b);
    }

    ufc(b).parent = a;
    ufc(a).size += ufc(b).size;
}

int main() {
    int n, m, src_x, src_y, dst_x, dst_y;

    {
        std::ifstream in("padure.in");
        in >> n >> m >> src_x >> src_y >> dst_x >> dst_y;
        for(s16 x = 0; x < n; x++) {
            for(s16 y = 0; y < n; y++) {
                // read type
                in >> uf[x][y].type;
                // initialize union find
                uf[x][y].parent = {x, y};
                uf[x][y].size = 1;
            }
        }
    }

    // Merge adjacent same-type nodes.
    for(s16 x = 0; x < n; x++) {
        for(s16 y = 0; y < n; y++) {
            // Up and left is enough since union-find doesn't need merge from both sides of the edges.
            constexpr coords dirs[] = {{-1, 0}, {0, -1}};
            for(const auto &dir : dirs) {
                s16 x1 = x + dir.x, y1 = y + dir.y;
                // check OOB
                if(!(x1 > 0 && x1 < n && y1 > 0 && y1 < n)) {
                    continue;
                }
                // union
                if(uf[x1][y1].type == uf[x][y].type) {
                    union_merge({x1, y1}, {x, y});
                }
            }
        }
    }

    // Assign consecutive IDs to each set.
    // Reuse size as "ID".
    // Reuse type as "visited".
    s16 ids = 0;
    for(s16 x = 0;x < n;x++) {
        for(s16 y = 0;y < n;y++) {
            union_find_node &node = ufc(union_find({x, y}));
            if(node.type != CHAR_MAX) {
                node.type = CHAR_MAX;
                node.size = ids;
                ids++;
            }
        }
    }

    // Generate edges.
    std::vector<std::vector<s16>> edges(ids, std::vector<s16>(0));
    // TODO

    // Perform BFS.
    // TODO

    std::ofstream out("padure.out");
    out << "TODO\n";
    return 0;
}
