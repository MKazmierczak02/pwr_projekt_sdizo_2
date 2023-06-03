#include <gtest/gtest.h>
#include <iostream>
#include "../../Structures/GraphMatrix.cpp"

using namespace std;

TEST(GraphMatrix, GraphMatrix__Test)
{
    auto graph = GraphMatrix::graphMatrixloadFromFile("./graf2.txt");
    graph.displayMatrix();
    auto mst = graph.getMinimumSpanningTreeKruskal();
    cout << "\n\n";
//    mst.displayMatrix();
    auto mst2 = graph.getMinimumSpanningTreePrim();
    cout << "\n\n";
//    mst2.displayMatrix();
    EXPECT_EQ(0, 0);
}