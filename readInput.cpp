/*Hell world program in C++*/
#include <iostream>
#include <fstream>
#include <vector>
int main() {
    std::cout << "Hello World!" << std::endl;
    std::ifstream inputFile("test.gr");
    std::string line;
    std::vector<int> A, B;
    std::vector<std::pair<int, int> > edges;
    int n0, n1, m;
    A.clear();
    B.clear();
    while (std::getline(inputFile, line))
    {
        
        if (line[0] == 'c') {
            continue;
        }
        if (line.substr(0, 5) == "p ocr") {            
            std::sscanf(line.c_str(),"p ocr %d %d %d", &n0, &n1, &m);
            // std::cout << n0 << " " << n1 << " " << m << std::endl;
            for (int i = 1; i <= std::max(n0, n1); i++)
            {
                if (i <= n0) {
                    A.push_back(i);
                }
                if (i <= n1) {
                    B.push_back(i + n0);
                }
            }
            //print vector A
            std::cout << "A: " << std::endl;
            for (int i = 0; i < A.size(); i++)
            {
                std::cout << A[i] << " ";
            }
            std::cout << "\nB: " <<std::endl;
            for (int i = 0; i < B.size(); i++)
            {
                std::cout << B[i] << " ";
            }
            continue;
        }
        
    }
    // kode der laver de 3 arrays xD
    inputFile.close();
    return 1;
}



