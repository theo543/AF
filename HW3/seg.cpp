#include <algorithm>
#include <numeric>
#include <fstream>
#include <iomanip>
#include <climits>
#include <limits>
#include <cmath>

// https://en.wikipedia.org/wiki/Held-Karp_algorithm

void minimize(double &target, double new_val) {
    target = std::min(target, new_val);
}

const int max_nodes = 17;
const unsigned int max_masks = 1 << (max_nodes - 1);

#if __cplusplus >= 202002L
#define POPCOUNT std::popcount
#else
#define POPCOUNT __builtin_popcount
#endif

bool has_bit(int mask, int bit) {
    return mask & (1 << bit);
}

struct point {
    double x;
    double y;
};
double dist(const point &a, const point &b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

const int ends[] = {0, 1};

double solve_test(std::ifstream &in) {
    static double dp_dist[max_masks][max_nodes - 1][2];
    point segs[max_nodes][2];
    int n;

    std::fill(&dp_dist[0][0][0], &dp_dist[0][0][0] + sizeof(dp_dist)/sizeof(double), std::numeric_limits<double>::infinity());

    in >> n;
    for(int x = 0;x < n;x++) {
        in >> segs[x][0].x >> segs[x][0].y >> segs[x][1].x >> segs[x][1].y;
    }

    if(n == 1) {
        return 0;
    }

    for(int x = 0;x < n - 1;x++) {
        dp_dist[1 << x][x][1] = dist(segs[x][0], segs[n - 1][0]);
        dp_dist[1 << x][x][0] = dist(segs[x][1], segs[n - 1][0]);
    }

    unsigned int masks = 1 << (n - 1);
    unsigned int bitmasks[max_masks + 1];
    std::iota(bitmasks, bitmasks + masks, 0);
    std::sort(bitmasks, bitmasks + masks, [](unsigned int b1, unsigned int b2){return POPCOUNT(b1) < POPCOUNT(b2);});
    bitmasks[masks] = UINT_MAX;
    for(unsigned int mask : bitmasks) {
        if(mask == UINT_MAX) {
            break;
        }
        if(POPCOUNT(mask) < 2) {
            continue;
        }
        for(int to = 0;to < n - 1;to++) {
            if(!has_bit(mask, to)) {
                continue;
            }
            for(int from = 0;from < n - 1;from++) {
                if(from == to || !has_bit(mask, from)) {
                    continue;
                }
                int prevMask = mask & ~(1 << to);
                for(int fromEnd : ends) {
                    for(int toEnd : ends) {
                        double newDist = dp_dist[prevMask][from][fromEnd] + dist(segs[from][fromEnd], segs[to][toEnd]);
                        minimize(dp_dist[mask][to][1 - toEnd], newDist);
                    }
                }
            }
        }
    }
    int fullMask = masks - 1;
    double bestDist = std::numeric_limits<double>::infinity();
    for(int x = 0;x < n - 1;x++) {
        for(int end : ends) {
            double newDist = dp_dist[fullMask][x][end] + dist(segs[n - 1][1], segs[x][end]);
            minimize(bestDist, newDist);
        }
    }
    return bestDist;
}

int main() {
    std::ifstream in("seg.in");
    std::ofstream out("seg.out");
    int tests;
    in >> tests;
    while(tests--) {
        out << std::fixed << std::setprecision(6) << solve_test(in) << '\n';
    }
}
