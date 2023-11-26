#include <fstream>
#include <cmath>

#include "graph.cpp"

#include <limits>
#include <iomanip>

struct point {
    long double x, y;
};

long double distance(const point &p1, const point &p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

int main() {
    std::ifstream in("cablaj.in");
    std::ofstream out("cablaj.out");
    uint n;
    in >> n;
    std::vector<point> points(n);
    union_find uf {std::vector<uint>(n), std::vector<uint>(n, 1)};
    for(uint x = 0;x < n;x++) {
        uf.parent[x] = x;
        in >> points[x].x >> points[x].y;
    }
    std::vector<long double> distances(n);
    for(uint x = 0;x < n;x++) {
        distances[x] = distance(points[0], points[x]);
    }
    long double sum = 0;
    // it's a dense graph, so exhaustive search is optimal
    for(uint x = 1;x < n;x++) {
        long double min = std::numeric_limits<long double>::max();
        uint min_index = 0;
        for (uint y = 0; y < n; y++) {
            if (uf.find(y) != uf.find(0) && distances[y] < min) {
                min = distances[y];
                min_index = y;
            }
        }
        sum += min;
        uf.merge(0, min_index);
        for (uint y = 0; y < n; y++) {
            const auto new_distance = distance(points[min_index], points[y]);
            distances[y] = std::min(distances[y], new_distance);
        }
    }
    assert(sum <= 900000000.0 * 9000.0 * 10.0);
    out << std::fixed << std::setprecision(6) << sum << '\n';
}
