#include <fstream>
#include <deque>
#include <cstring>
char types[1000][1000];
int dist[1000][1000];
int main() {
    memset(dist, CHAR_MAX, sizeof(dist));
    int n, m;
    int src_x, src_y, dst_x, dst_y;
    {
        std::ifstream in("padure.in");
        in >> n >> m >> src_x >> src_y >> dst_x >> dst_y;
        src_x--; src_y--; dst_x--; dst_y--;
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < m; y++) {
                in >> types[x][y];
            }
        }
    }

    struct coord {
        int x, y;
    };
    std::deque<coord> bfs;
    bfs.push_back({src_x, src_y});
    dist[src_x][src_y] = 0;
    while(!bfs.empty()) {
        coord c = bfs.front();
        bfs.pop_front();
        if(c.x == dst_x && c.y == dst_y) {
            std::ofstream out("padure.out");
            out << dist[c.x][c.y] << "\n";
            return 0;
        }
        constexpr coord dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for(const coord &d : dirs) {
            int x1 = c.x + d.x, y1 = c.y + d.y;
            if(x1 < 0 || x1 >= n || y1 < 0 || y1 >= m) {
                continue;
            }
            bool cost = types[c.x][c.y] != types[x1][y1];
            if(cost + dist[c.x][c.y] < dist[x1][y1]) {
                dist[x1][y1] = cost + dist[c.x][c.y];
                if(cost) {
                    bfs.push_back({x1, y1});
                } else {
                    bfs.push_front({x1, y1});
                }
            }
        }
    }

    __builtin_trap();
}
