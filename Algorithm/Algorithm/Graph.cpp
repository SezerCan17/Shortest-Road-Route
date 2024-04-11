// Graph.cpp

#include "Graph.h"

Graph::Graph(int vertices) : vertices(vertices) {
    // Constructor implementation
}

void Graph::addVertex(std::string city) {
    // Adds a new vertex (city) to the graph.
    cityNames.push_back(city);
}

void Graph::addEdge(int source, int destination, int distance) {
    // Adds an edge (road) between two vertices (cities) with a specified distance.
    adjacencyList[source].push_back(std::make_pair(destination, distance));
}

int Graph::getVertices() {
    // Getter for the number of vertices in the graph.
    return vertices;
}

void Graph::setVertices(int vertices) {
    // Setter for the number of vertices in the graph.
    this->vertices = vertices;
}

std::vector<std::string> Graph::getCityNames() {
    // Getter for the names of cities in the graph.
    return cityNames;
}

void Graph::sortEdges() {
    // Sorts the edges of each vertex in non-decreasing order based on distance.
    for (int i = 0; i < vertices; i++) {
        std::sort(adjacencyList[i].begin(), adjacencyList[i].end(), [](const auto& left, const auto& right) {
            return left.second < right.second;
            });
    }
}

void Graph::printGraph() {
    // Prints the graph, showing the vertices and their connected edges.
    for (int u = 0; u < vertices; u++) {
        int v, w;
        std::cout << " " << cityNames[u] << " is connected to:\n";
        for (auto it = adjacencyList[u].begin(); it != adjacencyList[u].end(); it++) {
            v = it->first;
            w = it->second;
            std::cout << "\t" << cityNames[v] << " (Distance: " << w << " km)\n";
        }
        std::cout << "\n";
    }
}

void Graph::printKClosestCities(int cityIndex, int k) {
    // Prints the k closest cities to a given city.
    int v, w;
    std::cout << " " << cityNames[cityIndex] << " is connected to:\n";

    int i = 0;
    for (auto it = adjacencyList[cityIndex].begin(); it != adjacencyList[cityIndex].end(); it++) {
        v = it->first;
        w = it->second;

        std::cout << "\t" << cityNames[v] << " (Distance: " << w << " km)\n";

        i++;
        if (i == k) {
            break;
        }
    }
}

int Graph::dijkstra(std::string source, std::string destination) {
    // Finds the shortest path between two cities using Dijkstra's algorithm.
    int sourceIndex;
    int destinationIndex;
    int count = 0;
    for (int i = 0; i < vertices; i++) {
        if (source == cityNames[i]) {
            sourceIndex = i;
            count++;
        }
        if (destination == cityNames[i]) {
            destinationIndex = i;
            count++;
        }
    }
    if (count != 2) {
        return 0;
    }

    std::vector<int> distance(vertices, std::numeric_limits<int>::max());
    std::vector<int> parent(vertices, -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distance[sourceIndex] = 0;
    pq.push(std::make_pair(0, sourceIndex));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : adjacencyList[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push(std::make_pair(distance[v], v));
            }
        }
    }

    printDijkstraResult(sourceIndex, destinationIndex, parent, distance);
    return 1;
}

void Graph::printDijkstraResult(int source, int destination, const std::vector<int>& parent, const std::vector<int>& distance) {
    // Helper function to print the result of Dijkstra's algorithm.
    std::cout << "Shortest path from " << cityNames[source] << " to " << cityNames[destination] << ":\n";
    printPath(destination, parent);
    std::cout << "\nTotal distance: " << distance[destination] << " km\n";
}

void Graph::printPath(int current, const std::vector<int>& parent) {
    // Helper function to print the path found by Dijkstra's algorithm.
    if (current == -1) return;
    printPath(parent[current], parent);
    std::cout << cityNames[current];
    if (current != parent.size() - 1) std::cout << " -> ";
}

int Graph::takeDistance(int o, int j, std::vector<std::string> userString2[]) {
    // Parses the distance between two cities from the userString2 array.
    int distanceInt = std::stoi(userString2[o + 1][j + 2]);
    return distanceInt;
}

std::string fixCityName(std::string cityName) {
    // Helper function to fix the format of city names (if needed).
    if (!cityName.empty()) {
        cityName[0] = std::toupper(cityName[0]);
        for (size_t i = 1; i < cityName.length(); ++i) {
            cityName[i] = std::tolower(cityName[i]);
        }
    }
    return cityName;
}
