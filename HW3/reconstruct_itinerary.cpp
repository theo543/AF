#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>

#include "graph.cpp"

class Solution {
public:
    static std::vector<std::string> findItinerary(const std::vector<std::vector<std::string>>& tickets_in_nested_vec) {
        struct ticket {
            std::string from;
            std::string to;
        };
        std::vector<ticket> tickets;
        std::set<std::string> airports;
        for(const auto &v : tickets_in_nested_vec) {
            tickets.push_back({v[0], v[1]});
            airports.insert(v[0]);
            airports.insert(v[1]);
        }
        std::sort(tickets.begin(), tickets.end(), [](const ticket &a, const ticket &b) {
            return a.from < b.from || (a.from == b.from && a.to < b.to);
        });
        std::unordered_map<std::string, uint> airport_to_id;
        std::vector<std::string> id_to_airport;
        uint id = 0;
        uint start_node = UINT64_MAX;
        for(const auto &airport : airports) {
            if(airport == "JFK") {
                start_node = id;
            }
            airport_to_id[airport] = id;
            id_to_airport.push_back(airport);
            id++;
        }
        assert(start_node != UINT64_MAX);
        graph g;
        g.grow(airports.size());
        for(const auto &t : tickets) {
            g.add_edge(airport_to_id[t.from], airport_to_id[t.to], 1);
        }
        const auto &path = g.eulerian_cycle(start_node);
        std::vector<std::string> result;
        std::transform(path.begin(), path.end(), std::back_inserter(result), [&id_to_airport](uint id) {
            return id_to_airport[id];
        });
        return result;
    }
};
