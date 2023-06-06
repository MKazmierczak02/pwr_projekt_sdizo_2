#include <gtest/gtest.h>
#include <iostream>
#include "../../Structures/GraphList.cpp"
using namespace std;

TEST(GraphList, GraphList_Kruskal_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./mst_1.txt");
    graph.displayList();
    graph.MinimumSpanningTreeKruskal();
    EXPECT_EQ(0, 0);
}

TEST(GraphList, GraphList_Prim_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./mst_2.txt");
    graph.displayList();
    graph.MinimumSpanningTreePrim();
    cout << "\n\n";

    EXPECT_EQ(0, 0);
}

TEST(GraphList, GraphList_Dijkstra_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./path_1.txt");
    graph.shortestPathDijkstra();
    cout << "\n\n";
    EXPECT_EQ(0, 0);
}

TEST(GraphList, GraphList_BellmanFord_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./path_1.txt");
    graph.shortestPathbellmanFord();
    cout << "\n\n";
    EXPECT_EQ(0, 0);
}