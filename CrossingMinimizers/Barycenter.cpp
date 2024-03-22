#include "Barycenter.h"
#include <algorithm>

Barycenter::Barycenter(Graph* graph, std::string solutionFileName) : CrossingMinimizer(graph, solutionFileName)
{
    
}




bool compareBarycenterValues(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void Barycenter::minimizeCrossings() {
    std::vector<Vertex> B = *graph->getB();
    std::vector <std::pair<float, Vertex> > barycenterValues;
    for (int i = 0; i < B.size(); i++)
    {
        float barycenterValue = 0;
        for (Vertex* edgeVertex : B.at(i).getEdges()) {
            barycenterValue += edgeVertex->getVertexID();
        }
        barycenterValue = barycenterValue / B.at(i).getEdges().size();
        barycenterValues.push_back(std::make_pair(barycenterValue, B.at(i)));
    }

    std::sort(barycenterValues.begin(), barycenterValues.end(), compareBarycenterValues);

    for (int i = 0; i < barycenterValues.size(); i++)
    {
        B.at(i) = barycenterValues.at(i).second;
    }

    writeSolution(&B);
}




Barycenter::~Barycenter()
{
}
