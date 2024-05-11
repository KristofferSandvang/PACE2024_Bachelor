#include "OptimizedBCRight.h"
#include <algorithm>
#include <map>
#include <iostream>

OptimizedBCRight::OptimizedBCRight(Graph* graph) : CrossingMinimizer(graph) {

}

void OptimizedBCRight::optimizeOrder(std::vector<int>* vertexIndices) {
    //std::cout << "1Number of same bc val: " << vertexIndices.size() << std::endl;
    // Kigge på forældre knuderne, også den der har den forældre med højst x, skal vi til sidst. 
    // Måske bedre at kigge på den laveste forældre knude?
    std::vector<std::pair<int, int> > order;
    for (int index: *vertexIndices) {
        std::vector<Vertex*> Parents = B.at(index).getEdges();
        auto minParent = std::min_element(Parents.begin(), Parents.end(),
        [](Vertex* a, Vertex*b) {
            return a->getVertexID() < b->getVertexID();
        });
        order.push_back(std::make_pair((*minParent)->getVertexID(), index));
    }

    std::sort(order.begin(), order.end(), 
    [](std::pair<int, int> a, std::pair<int, int> b){
        return a.first < b.first;
    });

    
    std::vector<Vertex> tmpB = B;
    for (int i = 0; i < order.size(); i++) {
        int index = order.at(i).second;
        if (index < 0 || index >= B.size()) {
            continue;
        }
        B.at(index) = tmpB.at(index);
    }
    B = tmpB;

}


void OptimizedBCRight::handleSameBCVal(std::vector<std::pair<float, Vertex> >* bcValues) {
    std::map<float, std::vector<int> > BCmap;
    for (int i = 0; i < bcValues->size(); i++)
    {
        B.at(i) = bcValues->at(i).second;
        BCmap[bcValues->at(i).first].push_back(i); 
    }

    for (auto& entry : BCmap) {
        std::vector<int>& vertices = entry.second;
        if (vertices.size() == 1) {
            continue;
        }
        optimizeOrder(&vertices);
    }
}


bool compareBCVALSRight(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void OptimizedBCRight::minimizeCrossings() {
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

    std::sort(barycenterValues.begin(), barycenterValues.end(), compareBCVALSRight);

    handleSameBCVal(&barycenterValues);

}


OptimizedBCRight::~OptimizedBCRight()
{
}
