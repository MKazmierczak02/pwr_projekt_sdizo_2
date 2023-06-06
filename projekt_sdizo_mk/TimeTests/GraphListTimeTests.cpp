#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include "../Structures/GraphList.cpp"
using namespace std;
class GraphGenerator {
public:
    static vector<GraphList> generateGraphInstances(int numInstances, int numVertices, double density) {
        random_device rd; // obiekt do tworzenia liczb losowych
        mt19937 gen(rd()); // generowanie liczb pseudolosowych
        uniform_real_distribution<double> dis(0.0, 1.0); // tworzy obiekt rozkładu jednorodnego

        vector<GraphList> instances;

        for (int i = 0; i < numInstances; ++i) {
            GraphList graph(numVertices, 0, 0);
            for (int u = 0; u < numVertices; ++u) {
                for (int v = u + 1; v < numVertices; ++v) {
                    if (dis(gen) <= density) {
                        int weight = rand() % 10 + 1;  // Losowa waga z zakresu 1-10
                        graph.addEdge(u, v, weight, false);  // Dodanie nieskierowanej krawędzi
                    }
                }
            }

            instances.push_back(graph);
        }

        return instances;
    }

    static long long int read_QPC()
    {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        return((long long int)count.QuadPart);
    }

    static void testTimeForIstances(vector<GraphList>& instances, int n, int dens) {
        string fileName = "graph_list_dijkstra_test.txt";
        ofstream file(fileName, ofstream::app);
        long long int frequency, start, elapsed;
        QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
        double sum = 0;
        for (int i = 0; i < instances.size(); ++i) {
            if (file.is_open()) {
//                file << "Graf" << i + 1 << ":\n";
                // liczenie czasu
                start = read_QPC();
                instances[i].shortestPathbellmanFord();
                elapsed = read_QPC() - start;

//                file <<  setprecision(5) << (float)elapsed /frequency << "\n"; //Time [s]
//                file << setprecision(5) << (1000.0 * elapsed) /frequency << "\n";   // Time [ms]
                sum += (1000.0 * elapsed) /frequency;
//                file << setprecision(5) << (1000000.0 * elapsed) /frequency << "\n"; // Time [us]
//                file << setprecision(5) << (1000000000.0 * elapsed) /frequency << "\n"; // "Time [ns]
            }
        }
        file << setprecision(5) << sum / instances.size() << "\n";
    }
};

int main() {
    int numInstances = 100;
    vector<int> numVertices = {10, 50, 100, 250, 500}; // rozmiary listy do przetestowania
    vector<double> density = {0.25, 0.5, 0.75, 0.99};
    for(int vertices : numVertices){
        int i=0;
        for (double iterdensity : density){
            vector<GraphList> instances = GraphGenerator::generateGraphInstances(numInstances, vertices, iterdensity);
            GraphGenerator::testTimeForIstances(instances, vertices, i);
            i++;
        }
        string fileName = "graph_list_dijkstra_test.txt";
        ofstream file(fileName, ofstream::app);
        file << "\n";
    }


    return 0;
}