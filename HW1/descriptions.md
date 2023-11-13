# Solutions

## From Leetcode

* 886 Possible Bipartition: Bipartition. ✅
* 210 Course Schedule II: Topological sort. ✅
* 1192 Critical Connections in a Network: Critical connections. ✅
* 802 Find Eventual Safe States: Topological sort. ✅
* 934 Shortest Bridge: BFS from multiple sources to find distance to one destination. 🟡 (✅ with optimized solution with no class)\
  This problem OOMs with 91/97 test cases passed. This isn't surprising, since the class is unnecessarily storing
  edges, when really the edges are completely regular up/down/left/right, and the problem designer definitely
  expected a solution optimized for the specific problem.
* 990 Satisfiability of Equality Equations: Connected components. Answer is found by checking if there is a "!=" relation in the same component. ✅

## From Codeforces

* 1144 F. Graph Without Long Directed Paths: Bipartition. ✅
* 1881 F. Minimum Maximum Distance: Can be solved with the two BFS diameter algorithm. ✅

## From Infoarena

* Padure 🟡 (✅ with optimized solution with no class)\
  Find the connected components.\
  Then create a new graph from the components / collapse the graph into components.\
  Then simple BFS on the new graph.

* Patrol2 🟡 (✅ with optimized solution with no class)\
  Create many parallel copies of the graph.
  Taking a step in a copy sends you to next copy, with the patrols advanced.
  The occupied nodes are deleted in each copy.
  The copies loop back around when all patrols are back at the original position.
  This means at most `7!` copies of the graph.

There are some OOM/timeout test case failures for these problems,
this isn't surprising since these the harder test cases require optimizations,
not a just general class. Especially for grid-type graph, there is memory waste storing the edges when they are regular.

The problems get 60/100 and 68/100 respectively.
