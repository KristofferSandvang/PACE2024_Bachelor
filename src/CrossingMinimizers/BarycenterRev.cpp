#include "BarycenterRev.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <math.h>

BarycenterRev::BarycenterRev(Graph* graph) : CrossingMinimizer(graph) {}

bool compareBCREVVALS(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void BarycenterRev::optimizeOrderBCREV(std::vector<int>* vertexIndices) {
    return;
}

void BarycenterRev::handleSameBCREVVal(std::vector<std::pair<float, Vertex> >* bcValues) {
    std::map<float, std::vector<int> > BCmap;
    for (int i = 0; i < bcValues->size(); i++) {
        BCmap[bcValues->at(i).first].push_back(i); 
    }

    for (auto& entry : BCmap) {
        std::vector<int>& indices = entry.second;
        if (indices.size() == 1) {
            continue;
        }
        std::reverse(indices.begin(), indices.end());
        for (int i = 0; i < indices.size(); i++) {
            B.at(indices[i]) = bcValues->at(indices[i]).second;
        }
    }
}

void BarycenterRev::minimizeCrossings() {

    std::vector <std::pair<float, Vertex> > barycenterValues;
    for (int i = 0; i < B.size(); i++) {
        float barycenterValue = 0;
        for (Vertex* edgeVertex : B.at(i).getEdges()) {
            barycenterValue += edgeVertex->getVertexID();
        }
        barycenterValue = barycenterValue / B.at(i).getEdges().size();
        barycenterValues.push_back(std::make_pair(barycenterValue, B.at(i)));
    }

    std::sort(barycenterValues.begin(), barycenterValues.end(), compareBCREVVALS);

    for (int i = 0; i < barycenterValues.size(); i++) {
        B.at(i) = barycenterValues.at(i).second;
    }
    handleSameBCREVVal(&barycenterValues);
}

BarycenterRev::~BarycenterRev() {}
