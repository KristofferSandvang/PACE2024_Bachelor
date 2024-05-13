#include "MedianRev.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <math.h>

MedianRev::MedianRev(Graph* graph) : CrossingMinimizer(graph)
{
}
bool compareMEDREVVALS(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void MedianRev::optimizeOrderMEDREV(std::vector<int>* vertexIndices) {
    return;
}


void MedianRev::handleSameMEDREVVal(std::vector<std::pair<float, Vertex> >* MedValues) {
    std::map<float, std::vector<int> > MedMap;
    for (int i = 0; i < MedValues->size(); i++)
    {
        MedMap[MedValues->at(i).first].push_back(i); 
    }

    for (auto& entry : MedMap) {
        std::vector<int>& indices = entry.second;
        if (indices.size() == 1) {
            continue;
        }
        std::reverse(indices.begin(), indices.end());
        for (int i = 0; i < indices.size(); i++) {
            B.at(indices[i]) = MedValues->at(indices[i]).second;
        }
    }
}

void MedianRev::minimizeCrossings() {
   std::vector <std::pair<float, Vertex> > medianValues;
    for (int i = 0; i < B.size(); i++){
        std::vector<int> edgeIDs;
        for (Vertex* edgeVertex : B.at(i).getEdges()) {
            edgeIDs.push_back(edgeVertex->getVertexID());
        }
        std::sort(edgeIDs.begin(), edgeIDs.end());
        float medianValue = 0;

        if (edgeIDs.empty()) {
            medianValue = 0;
        }
        else if (edgeIDs.size() % 2){
            // if odd
            medianValue = edgeIDs[floor(edgeIDs.size())/2];
        } else {
            // if even
            medianValue = edgeIDs[edgeIDs.size()/2];
        }
        
        medianValues.push_back(std::make_pair(medianValue, B.at(i)));
    }

    std::sort(medianValues.begin(), medianValues.end(), compareMEDREVVALS);

    for (int i = 0; i < medianValues.size(); i++)
    {
        B.at(i) = medianValues.at(i).second;
    }
    
    handleSameMEDREVVal(&medianValues);

}




MedianRev::~MedianRev()
{
}
