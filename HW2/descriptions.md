# Solutions

* Cablaj: ✅ MST. Prim with exhaustive search (dense graph). This _cannot_ work with the class. It is an Olympiad problem with **4736 KB** memory limit. Storing the edges will instantly cause MLE. I did still use the union-find from graph.cpp.
* Camionas: 🟡 Djikstra. (70/100, 3 tests have MLE) | ✅ (100/100, not using graph.cpp at all, but just a BFS 0-1. I tried implementing BFS 0-1 in the class, but it didn't help much with the MLE.)
* Trilant: ✅ Djikstra. You don't actually need to handle overlapping chains, since for any overlapping chain, there is a better solution that doesn't overlap, so Djikstra will avoid them for free.
* Dragoni: 🟡 Djikstra. N^2 * M (14/20 test cases => 52/100 points, MLE issues probably due to having to store n copies of the graph when really it could be done on the fly)
* Apm2: 🟡 MST. (20/100 with class) | ✅ (100/100, still using union-find from graph.cpp, but with modified Kruskal instead of class)
* 787 Cheapest Flights Within K Stops: ✅ Djikstra with one copy of the graph for each number of stops.
* 1489 Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree: ✅ MST. Needs a way to force an edge not to be used, and to be used. Modifying the cost is enough for this.
* Oracol: ✅ MST.
* Bile: ✅ Union-find.
* 1697 Checking Existence of Edge Length Limited Paths: ✅ Union-find.
