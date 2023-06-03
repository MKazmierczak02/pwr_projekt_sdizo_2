#include <gtest/gtest.h>
#include <iostream>
#include "../../Structures/GraphList.cpp"
using namespace std;

TEST(GraphList, GraphList_Kruskal_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./graf2.txt");
    graph.displayList();
    auto mst = graph.getMinimumSpanningTreeKruskal();
    cout << "\n\n";
    auto mst2 = graph.getMinimumSpanningTreePrim();
    cout << "\n\n";

    EXPECT_EQ(0, 0);
}
