#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream inputFile("tests/test.gr");
    std::string line;
    std::vector<int> A, B;
    std::vector<std::pair<int, int> > edges;
    int n0, n1, m;
    A.clear();
    B.clear();
    edges.clear();

    while (std::getline(inputFile, line))
    {
        if (line[0] == 'c') {
            continue;
        }
        if (line.substr(0, 5) == "p ocr") {            
            std::sscanf(line.c_str(),"p ocr %d %d %d", &n0, &n1, &m);
            
            for (int i = 1; i <= std::max(n0, n1); i++)
            {
                if (i <= n0) {
                    A.push_back(i);
                }
                if (i <= n1) {
                    B.push_back(i + n0);
                }
            }
        }

        int edgeStart, edgeEnd;
        if (std::sscanf(line.c_str(), "%d %d", &edgeStart, &edgeEnd) == 2)
        {
            std::pair<int, int> edge(edgeStart,edgeEnd);
            edges.push_back(edge);
        }
    }

    inputFile.close();
    return 0;
}



