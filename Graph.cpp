#include "Graph.h"
#include "CustomExceptions.h"

Graph::Graph(int Size, Graph::GraphType Type) {
    this->Size = Size;
    this->Type = Type;
	this->Edges = std::vector<std::vector<int> >(this->Size);
    this->Visited = std::vector<bool>(this->Size);
    SilentInitializer();
}

void Graph::SilentInitializer() {
    typedef std::vector<std::vector<int> >::iterator edge_outer_iterator;
    typedef std::vector<int>::iterator edge_inner_iterator;
    typedef std::vector<bool>::iterator visited_iterator;
    for (edge_outer_iterator outer_it = this->Edges.begin(); outer_it != this->Edges.end(); ++outer_it) {
        *outer_it = std::vector<int>(this->Size);
        for (edge_inner_iterator inner_it = outer_it->begin(); inner_it != outer_it->end(); ++inner_it) {
            *inner_it = 0;
        }
    }

    for (visited_iterator it = this->Visited.begin(); it != this->Visited.end(); ++it) {
        *it = false;
    }
}

void Graph::AddEdge(int start, int end) {
    if (this->Type == Graph::DIRECTED_WEIGHTED_GRAPH ||
        this->Type == Graph::UNDIRECTED_WEIGHTED_GRAPH) {
        throw CustomExceptions::NotAssigningWeightToWeightedGraphException();
    }

    if (start >= this->Size || start < 0) {
        throw CustomExceptions::GraphOutOfBoundsException(this->Size, start);
    }

    if (end >= this->Size || end < 0) {
        throw CustomExceptions::GraphOutOfBoundsException(this->Size, end);
    }

    if (this->Type == Graph::DIRECTED_UNWEIGHTED_GRAPH) {
        this->Edges[start][end] = 1;
    }
    else if (this->Type == Graph::UNDIRECTED_UNWEIGHTED_GRAPH) {
        this->Edges[start][end] = 1;
        this->Edges[end][start] = 1;
    }
}

void Graph::AddEdge(int start, int end, int weight) {
    if (this->Type == Graph::DIRECTED_UNWEIGHTED_GRAPH ||
        this->Type == Graph::UNDIRECTED_UNWEIGHTED_GRAPH) {
        throw CustomExceptions::AssigningWeightToUnWeightedGraphException();
    }

    if (start >= this->Size || start < 0) {
        throw CustomExceptions::GraphOutOfBoundsException(this->Size, start);
    }

    if (end >= this->Size || end < 0) {
        throw CustomExceptions::GraphOutOfBoundsException(this->Size, end);
    }

    if (this->Type == Graph::DIRECTED_WEIGHTED_GRAPH) {
        this->Edges[start][end] = weight;
    }
    else if (this->Type == Graph::UNDIRECTED_WEIGHTED_GRAPH) {
        this->Edges[start][end] = weight;
        this->Edges[end][start] = weight;
    }
}

void Graph::RemoveEdge(int start, int end) {
    if (this->Edges[start][end] == 0) {
        throw CustomExceptions::EdgeNotExistException(start, end);
    }

    if (start >= this->Size || start < 0) {
        throw CustomExceptions::GraphOutOfBoundsException(this->Size, start);
    }

    if (end >= this->Size || end < 0) {
        throw CustomExceptions::GraphOutOfBoundsException(this->Size, end);
    }

    if (this->Type == Graph::DIRECTED_WEIGHTED_GRAPH ||
        this->Type == Graph::DIRECTED_UNWEIGHTED_GRAPH) {
        this->Edges[start][end] = 0;
    }
    else if (this->Type == Graph::UNDIRECTED_WEIGHTED_GRAPH ||
            this->Type == Graph::UNDIRECTED_UNWEIGHTED_GRAPH) {
        this->Edges[start][end] = 0;
        this->Edges[end][start] = 0;
    }
}

void Graph::PrintGraph() {
    for (int i = 0; i < this->Size; i++) {
        for (int j = 0; j < this->Size; j++) {
            std::cout << this->Edges[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void Graph::DepthFirstTraversal(int start) {
    if (start >= this->Size || start < 0) {
        throw CustomExceptions::GraphOutOfBoundsException(this->Size, start);
    }
    std::vector<bool> visited = std::vector<bool>(this->Size);
    std::cout << "Depth First Traversal Started" << std::endl;
    Graph::DepthFirstTraversal(start, visited);
    std::cout << "Depth First Traversal Finished" << std::endl;
}

void Graph::DepthFirstTraversal(int start, std::vector<bool> &visited) {
    visited[start] = true;
    std::cout << start << std::endl;
    for (int c = 0; c < this->Size; c++) {
        if ((this->Edges[start][c] != 0) && (visited[c] == false)) {
            Graph::DepthFirstTraversal(c, visited);
        }
    }
}

void Graph::BreadthFirstTraversal(int start) {
    if (start >= this->Size || start < 0) {
        throw CustomExceptions::GraphOutOfBoundsException(this->Size, start);
    }
    std::queue<int> q = std::queue<int>();
    std::vector<bool> visited = std::vector<bool>(this->Size);
    for (int i = 0; i < visited.size(); i++) {
        visited[i] = false;
    }
    q.push(start);

    std::cout << "Breadth First Traversal Started" << std::endl;
    while (!q.empty()) {
        int temp = q.front();
        q.pop();
        if (!visited[temp]) {
            visited[temp] = true;
            std::cout << temp << std::endl;
        }

        for (int c = 0; c < this->Size; c++) {
            if ((this->Edges[temp][c] != 0) && (visited[c] == false)) {
                q.push(c);
            }
        }
    }
    std::cout << "Breadth First Traversal Finished" << std::endl;
}

std::vector<std::vector<int> > Graph::AsMatrix() {
    return this->Edges;
}

std::vector<Edge> Graph::GetEdges() {
    std::vector<Edge> edges = std::vector<Edge>();
    if (this->Type == Graph::DIRECTED_UNWEIGHTED_GRAPH ||
        this->Type == Graph::UNDIRECTED_UNWEIGHTED_GRAPH) {
        Edge temp;
        for (int i = 0; i < this->Size; i++) {
            for (int j = 0; j < this->Size; j++) {
                if (this->Edges[i][j] != 0) {
                    temp = Edge();
                    temp.Start = i;
                    temp.End = j;
                    edges.push_back(temp);
                }
            }
        }
    }
    else if (this->Type == Graph::DIRECTED_WEIGHTED_GRAPH ||
        this->Type == Graph::UNDIRECTED_WEIGHTED_GRAPH) {
        WeightedEdge temp;
        for (int i = 0; i < this->Size; i++) {
            for (int j = 0; j < this->Size; j++) {
                if (this->Edges[i][j] != 0) {
                    temp = WeightedEdge();
                    temp.Start = i;
                    temp.End = j;
                    temp.Weight = this->Edges[i][j];
                    edges.push_back(temp);
                }
            }
        }
    }
    return edges;
}