#include <iostream>
#include "Assignment.h"
#include <queue> 
#include "../Vertex.h"
#include <limits>


Assignment::Assignment(Graph* graph) : CrossingMinimizer(graph)
{
    adjacencyMatrix = graph->createAdjacencyMatrix();
    createCrossingMatrix(graph);
}


void Assignment::createCrossingMatrix(Graph* graph) {
    int m = graph->getn1();
    int n = graph->getn0();
    crossingMatrix.resize(m, std::vector<int>(m)); 

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            crossingMatrix[j][i] = calculateCost(i, j, n, m);
        }
    }
}

int Assignment::calculateCost(int i, int j, int n, int m) {
    int cost = 0;
    for (int h = 0; h < n; h++) {
        int tempSum = 0;
        for (int c = 0; c < m; c++) {
            for (int d = 0; d < n; d++) {
                if ((c > j && d < h) || (c < j && d > h)) {
                    tempSum++;
                }
            }
        }
        cost += adjacencyMatrix[h][i] * tempSum;
    }
    return cost;
}



// Modified version of the code shown on: https://en.wikipedia.org/wiki/Hungarian_algorithm
bool ckmin(int &a, const int &b) { return b < a ? a = b, 1 : 0; }

std::vector<int> Assignment::hungarianReduction() {
    const int J = crossingMatrix.size();
    const int W = crossingMatrix[0].size();
    // job[w] = job assigned to w-th worker, or -1 if no job assigned
    // note: a W-th worker was added for convenience
    std::vector<int> job(W, -1);
    std::vector<int> ys(J), yt(W + 1);  // potentials
    // -yt[W] will equal the sum of all deltas
    const int inf = std::numeric_limits<int>::max();
    for (int j_cur = 0; j_cur < J; ++j_cur) {  // assign j_cur-th job
        int w_cur = W;
        job[w_cur] = j_cur;
        // min reduced cost over edges from Z to worker w
        std::vector<int> min_to(W + 1, inf);
        std::vector<int> prv(W + 1, -1);  // previous worker on alternating path
        std::vector<bool> in_Z(W + 1);    // whether worker is in Z
        while (job[w_cur] != -1) {   // runs at most j_cur + 1 times
            in_Z[w_cur] = true;
            const int j = job[w_cur];
            int delta = inf;
            int w_next;
            for (int w = 0; w < W; ++w) {
                if (!in_Z[w]) {
                    if (ckmin(min_to[w], crossingMatrix[j][w] - ys[j] - yt[w])) {
                        prv[w] = w_cur;
                    }
                    if (ckmin(delta, min_to[w])) {
                        w_next = w;
                    }
                }
            }
            // delta will always be non-negative,
            // except possibly during the first time this loop runs
            // if any entries of C[j_cur] are negative
            for (int w = 0; w <= W; ++w) {
                if (in_Z[w]) {
                    ys[job[w]] += delta;
                    yt[w] -= delta;
                } 
                else {
                    min_to[w] -= delta;
                }
            }
            w_cur = w_next;
        }
        for (int w; w_cur != W; w_cur = w) {
            job[w_cur] = job[w = prv[w_cur]];
        }
    }
    return job;
}

void Assignment::minimizeCrossings() {
    std::vector<int> jobs = hungarianReduction();
    // updating B based on the new Positions
    /* std::cout << "??" << std::endl;
    std::cout << "Assignments:" << std::endl; */
   /*  for (int i = 0; i < jobs.size(); i++) {
        std::cout << "Worker " << i << ": Job " << jobs[i] << std::endl;
    } */
    std::vector<Vertex> tmpB;
    tmpB.resize(B.size());
    std::cout << "B = " << B.size() << ", jobs = " << jobs.size() << std::endl;
    for (int i = 0; i < B.size(); i++)
    {
        tmpB.at(jobs.at(i)) = B.at(i);
    }
    
    B = tmpB;
    std::cout << "updated B" << std::endl;
}

Assignment::~Assignment()
{

}
