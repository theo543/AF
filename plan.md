# Requirements from each problem

## From Leetcode

* 886 Possible Bipartition:\
  Class needs bipartition algorithm.\
* 210 Course Schedule II:\
  Class needs topological sort algorithm.\
  Therefore class must support directed graphs.\
  Problem only requires bool answer.
* 1192 Critical Connections in a Network:\
  Class needs critical edges algorithm for undirected graph.\
  Problem requires a list of all critical edges.
* 802 Find Eventual Safe States:\
  Class must be able to invert edges.\
  Problem is then solved with topological sort.\
  Problem requires list of all satisfiable nodes, not just bool answer.
* 934 Shortest Bridge:\
  Class must be able to BFS from multiple sources to one destination.\
  Problem only requires distance, not an exact path.
* 990 Satisfiability of Equality Equations:\
  Class must be able to find connected components.\
  Answer is found by checking if there is a "!=" relation in the same component.\
  Therefore class must say which nodes are in which components (not just number of components or something).

## From Codeforces

Since graph is given from stdin, class needs a way to manually add nodes and edges, and a way to initialize an initially empty graph.

* 1144 F. Graph Without Long Directed Paths\
  Can be solved with bipartition.\
  Bool answer not sufficient.
* 1881 F. Minimum Maximum Distance\
  Can be solved with the two BFS diameter algorithm.

## From Infoarena

* Padure\
  Find the connected components.\
  Then create a new graph from the components / collapse the graph into components.\
  Then simple BFS on the new graph.

* Patrol2\
  Create many parallel copies of the graph.
  Taking a step in a copy sends you to next copy, with the patrols advanced.
  The occupied nodes are deleted in each copy.
  The copies loop back around when all patrols are back at the original position.
  This means at most `7!` copies of the graph.
