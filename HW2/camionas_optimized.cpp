#include <fstream>
#include <vector>
#include <deque>
#include <cassert>

#define lint long long int

struct edge {
    lint to, cost;
};

int main() {
    std::ifstream in("camionas.in");
    std::ofstream out("camionas.out");
    lint n, m, g;
    in >> n >> m >> g;
    std::vector<std::vector<edge>> edges(n);
    for(lint x = 0;x < m;x++) {
        lint a, b, c;
        in >> a >> b >> c;
        a--; b--;
        edges.at(a).push_back({b, c < g ? 1 : 0});
        edges.at(b).push_back({a, c < g ? 1 : 0});
    }
    std::deque<lint> q;
    std::vector<lint> dist(n, n * 2);
    dist.at(0) = 0;
    q.push_back(0);
    while(!q.empty()) {
        lint node = q.front();
        q.pop_front();
        for(const auto& e : edges.at(node)) {
            lint new_dist = e.cost + dist.at(node);
            if(new_dist >= dist.at(e.to)) {
                continue;
            }
            if(e.cost) {
                q.push_back(e.to);
            } else {
                q.push_front(e.to);
            }
            dist.at(e.to) = new_dist;
        }
    }
    assert(dist.at(n - 1) != n * 2);
    out << dist.at(n - 1) << '\n';
}
