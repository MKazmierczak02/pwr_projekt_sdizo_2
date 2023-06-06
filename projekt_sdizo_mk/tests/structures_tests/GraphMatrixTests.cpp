#include <gtest/gtest.h>
#include <iostream>
#include "../../Structures/GraphMatrix.cpp"

using namespace std;

TEST(GraphMatrix, GraphMatrix_Kruskal_Test)
{
    auto graph = GraphMatrix::graphMatrixloadFromFile("./graf.txt");
    graph.displayMatrix();
    graph.MinimumSpanningTreeKurskal();
    cout << "\n\n";
    graph.MinimumSpanningTreePrim();
    cout << "\n\n";
    EXPECT_EQ(0, 0);
}

TEST(GraphMatrix, GraphMatrix_Prim_Test)
{
    auto graph = GraphMatrix::graphMatrixloadFromFile("./path_1.txt");
    graph.displayMatrix();
    graph.MinimumSpanningTreePrim();
    cout << "\n\n";
    graph.MinimumSpanningTreePrim();
    cout << "\n\n";
    EXPECT_EQ(0, 0);
}

TEST(GraphMatrix, GraphMatrix_Dijkstra_Test)
{
    auto graph = GraphMatrix::graphMatrixloadFromFile("./graf3.txt");
    cout << "\n\n";
    graph.shortestPathDijkstra();
    EXPECT_EQ(0, 0);
}

TEST(GraphMatrix, GraphMatrix_BellmanFord_Test)
{
    auto graph = GraphMatrix::graphMatrixloadFromFile("./graf3.txt");
    cout << "\n\n";
    graph.shortestPathBellmanFord();
    EXPECT_EQ(0, 0);
}