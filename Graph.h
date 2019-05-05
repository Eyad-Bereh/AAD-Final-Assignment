#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <iostream>
#include <queue>
#include "Edge.h"

class Graph {
public:
    enum GraphType {
		DIRECTED_WEIGHTED_GRAPH = 1,
		DIRECTED_UNWEIGHTED_GRAPH = 2,
        UNDIRECTED_WEIGHTED_GRAPH = 3,
		UNDIRECTED_UNWEIGHTED_GRAPH = 4
	};

private:
	int Size;
	std::vector<std::vector<int> > Edges;
	std::vector<bool> Visited;
    GraphType Type;

    void SilentInitializer();
    void DepthFirstTraversal(int, std::vector<bool>&);

public:
	Graph(int, GraphType);
    void AddEdge(int, int);
    void AddEdge(int, int, int);
    void RemoveEdge(int, int);
    void PrintGraph();
    void DepthFirstTraversal(int);
    void BreadthFirstTraversal(int);
    std::vector<std::vector<int> > AsMatrix();
    std::vector<Edge> GetEdges();
};

#endif