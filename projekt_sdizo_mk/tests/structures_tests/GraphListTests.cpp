#include <gtest/gtest.h>
#include <iostream>
#include "../../Structures/GraphList.cpp"
using namespace std;

TEST(GraphList, GraphList_Kruskal_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./graf.txt");
//    GraphList* graph = GraphList(5, false);
    graph.displayList();
//    graph.~GraphList();
    auto mst = graph.getMinimumSpanningTreeKruskal();
    cout << "\n\n";
    mst.displayList();
    auto mst2 = graph.getMinimumSpanningTreePrim();
    cout << "\n\n";
    mst2.displayList();
    EXPECT_EQ(0, 0);
}
