#include <fstream>
#include <cstdint>

// signed 16 bits
#define s16 int16_t

std::ifstream in("padure.in");
std::ofstream out("padure.out");

struct coords {
    s16 x;
    s16 y;
};

struct union_find_node {
    coords parent;
    s16 size;
    char type;
};

const coords dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

union_find_node uf[1000][1000];

void merge(coords a, coords b) {

}

int main() {
    int n, m, src_x, src_y, dst_x, dst_y;
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
    for(s16 x = 0; x < n; x++) {
        for(s16 y = 0; y < n; y++) {
            for(const auto &dir : dirs) {
                s16 x1 = x + dir.x, y1 = y + dir.y;
                // check OOB
                if(!(x1 > 0 && x1 < n && y1 > 0 && y1 < n)) {
                    continue;
                }
                // union
                if(uf[x1][y1].type == uf[x][y].type) {
                    merge({x1, y1}, {x, y});
                }
            }
        }
    }
}
