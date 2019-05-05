#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
	Graph graph(9, Graph::UNDIRECTED_UNWEIGHTED_GRAPH);

    graph.AddEdge(0, 4);
    graph.AddEdge(1, 4);
    graph.AddEdge(2, 1);
    graph.AddEdge(3, 2);
    graph.AddEdge(4, 5);
    graph.AddEdge(6, 3);
    graph.AddEdge(8, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(6, 7);
    graph.AddEdge(7, 5);
    graph.AddEdge(8, 6);

    std::vector<Edge> temp = graph.GetEdges();
    for (int i = 0; i < temp.size(); i++) {
        cout << "(" << temp[i].Start << ", " << temp[i].End << ")" << endl;
    }

	cin.get();
	return 0;
}