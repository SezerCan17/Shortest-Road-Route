// Graph.h

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>

class Graph {
public:
    Graph(int vertices);
    int takeDistance(int o, int j, std::vector<std::string> userString2[]);

    void addVertex(std::string city);
    void addEdge(int source, int destination, int distance);

    int getVertices();
    void setVertices(int vertices);

    std::vector<std::string> getCityNames();

    void sortEdges();
    void printGraph();
    void printKClosestCities(int cityIndex, int k);
    int dijkstra(std::string source, std::string destination);
  
private:
    int vertices;
    std::vector<std::string> cityNames;
    std::vector<std::pair<int, int>> adjacencyList[81];

    void printDijkstraResult(int source, int destination, const std::vector<int>& parent, const std::vector<int>& distance);
    void printPath(int current, const std::vector<int>& parent);
};

std::string fixCityName(std::string cityName);

#endif
