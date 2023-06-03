#include <gtest/gtest.h>
#include <iostream>
#include "../../Structures/GraphMatrix.cpp"

using namespace std;

//TEST(GraphMatrix, GraphMatrix_MST_Test)
//{
//    auto graph = GraphMatrix::graphMatrixloadFromFile("./graf.txt");
//    graph.displayMatrix();
//    graph.getMinimumSpanningTreeKruskal();
//    cout << "\n\n";
//    graph.getMinimumSpanningTreePrim();
//    cout << "\n\n";
//    EXPECT_EQ(0, 0);
//}

TEST(GraphMatrix, GraphMatrix_ND_Test)
{
    auto graph = GraphMatrix::graphMatrixloadFromFile("./graf3.txt");
    cout << "\n\n";
    graph.shortestPathDijkstra();
    EXPECT_EQ(0, 0);
}