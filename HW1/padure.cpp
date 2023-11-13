#include "graph.cpp"
#include <fstream>

int main() {
    std::ifstream cin("padure.in");
    assert(cin.good());
    assert(cin.is_open());
    std::ofstream cout("padure.out");
    const std::pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int n, m, src_line, src_col, dst_line, dst_col;

    cin >> n >> m >> src_line >> src_col >> dst_line >> dst_col;
    src_line--; src_col--; dst_line--; dst_col--;

    const auto is_oob = [&](int i, int j) {
        return i < 0 || i >= n || j < 0 || j >= m;
    };

    std::vector<std::vector<int>> type(n, std::vector<int>(m));
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            cin >> type[i][j];
        }
    }

    // create a graph with only same-type neighbours, to get connected components
    graph g;
    g.grow(n * m);
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            for(const auto &d : dirs) {
                int i2 = i + d.first, j2 = j + d.second;
                if(!is_oob(i2, j2) && type[i][j] == type[i2][j2]) {
                    g.add_edge(i * m + j, i2 * m + j2);
                }
            }
        }
    }
    auto comp = g.components();
    g = graph();
    g.grow(comp.size());
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            for(const auto &d : dirs) {
                int i2 = i + d.first, j2 = j + d.second;
                if(!is_oob(i2, j2) && comp[i * m + j] != comp[i2 * m + j2]) {
                    g.add_edge(comp[i * m + j], comp[i2 * m + j2]);
                }
            }
        }
    }
    auto bfs = g.bfs_distances({comp[src_line * m + src_col]});
    for(const auto &b : bfs) {
        if(b.node == comp[dst_line * m + dst_col]) {
            cout << b.distance << '\n';
            return 0;
        }
    }
}
