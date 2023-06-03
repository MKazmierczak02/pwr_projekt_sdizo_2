#include <gtest/gtest.h>
#include <iostream>
#include "../../Structures/GraphList.cpp"
using namespace std;

//TEST(GraphList, GraphList_Kruskal_TEST)
//{
//    GraphList graph = GraphList::graphListloadFromFile("./graf.txt");
//    graph.displayList();
//    graph.getMinimumSpanningTreeKruskal();
//    cout << "\n\n";
//    graph.getMinimumSpanningTreePrim();
//    cout << "\n\n";
//
//    EXPECT_EQ(0, 0);
//}

TEST(GraphList, GraphList_Dijkstra_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./graf3.txt");
    graph.shortestPathDijkstra();
    cout << "\n\n";
    EXPECT_EQ(0, 0);
}


