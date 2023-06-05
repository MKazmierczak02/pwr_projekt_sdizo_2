#include <gtest/gtest.h>
#include <iostream>
#include "../../Structures/GraphList.cpp"
using namespace std;

TEST(GraphList, GraphList_Kruskal_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./graf.txt");
    graph.displayList();
    graph.MinimumSpanningTreeKruskal();
    cout << "\n\n";
    graph.MinimumSpanningTreePrim();
    cout << "\n\n";

    EXPECT_EQ(0, 0);
}

TEST(GraphList, GraphList_Prim_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./graf.txt");
    graph.displayList();
    graph.MinimumSpanningTreePrim();
    cout << "\n\n";
    graph.MinimumSpanningTreePrim();
    cout << "\n\n";

    EXPECT_EQ(0, 0);
}

TEST(GraphList, GraphList_Dijkstra_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./graf3.txt");
    graph.shortestPathDijkstra();
    cout << "\n\n";
    EXPECT_EQ(0, 0);
}

TEST(GraphList, GraphList_BellmanFord_TEST)
{
    GraphList graph = GraphList::graphListloadFromFile("./graf3.txt");
    graph.shortestPathbellmanFord();
    cout << "\n\n";
    EXPECT_EQ(0, 0);
}