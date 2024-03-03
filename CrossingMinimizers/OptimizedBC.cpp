#include "OptimizedBC.h"
#include <algorithm>
#include <map>

OptimizedBC::OptimizedBC(Graph graph, std::string solutionFileName) : CrossingMinimizer(graph, solutionFileName)
{
    B = graph.getB();
}

void OptimizedBC::optimizeOrder(std::vector<Vertex> vertices) {
    int currentCrossings = graph.countCrossings(graph.getA(), B);
    // Skal gemme de skiftede verticer
    for (int i = 0; i < vertices.size(); i++)
    {
        Vertex firstVertex = vertices.at(i);
        for (int j = 0; j < vertices.size(); j++)
        {
            if (i == j) {
                continue;
            }
            Vertex secondVertex = vertices.at(j);
            std::swap(B.at(i), B.at(j));
            int newCrossings = graph.countCrossings(graph.getA(), B);
            if (newCrossings < currentCrossings) {
                currentCrossings = newCrossings;
            } else {
                std::swap(B.at(i), B.at(j));
            }
        }
        
    }
    
}


void OptimizedBC::handleSameBCVal(std::vector<std::pair<float, Vertex> > bcValues) {
    std::vector<Vertex> tempB;
    std::map<float, std::vector<Vertex> > BCmap;
    for (int i = 0; i < bcValues.size(); i++)
    {
        B.at(i) = bcValues.at(i).second;
        BCmap[bcValues.at(i).first].push_back(bcValues.at(i).second); 
    }

    for (auto& entry : BCmap) {
        std::vector<Vertex>& vertices = entry.second;
        if (vertices.size() == 1) {
            continue;
        }
        optimizeOrder(vertices);
        
    }
}


bool compareBarycenterValues(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void OptimizedBC::minimizeCrossings() {
    std::vector <std::pair<float, Vertex> > barycenterValues;
    for (int i = 0; i < B.size(); i++)
    {
        float barycenterValue = 0;
        for (Vertex edgeVertex : B.at(i).getEdges()) {
            barycenterValue += edgeVertex.getVertexID();
        }
        barycenterValue = barycenterValue / B.at(i).getEdges().size();
        barycenterValues.push_back(std::make_pair(barycenterValue, B.at(i)));
    }

    std::sort(barycenterValues.begin(), barycenterValues.end(), compareBarycenterValues);

    B = handleSameBCVal(barycenterValues);

    writeSolution(B);
}




OptimizedBC::~OptimizedBC()
{
}
