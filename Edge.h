#ifndef __EDGE_H__
#define __EDGE_H__

class Edge {
    public:
    int Start;
    int End;
};

class WeightedEdge : public Edge {
    public:
    int Weight;
};

#endif