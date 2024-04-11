#include <iostream>
#include "Graph.h"
#include <fstream>

std::string cityName;
std::string destinationCity;
int takeDistance(int o, int j, std::vector<std::string> userString2[]);
void enterCity(Graph& graph);
void printCity();

std::string fixCityName(std::string cityName);

int main() {
    // Create a Graph object with 0 vertices.
    Graph graph(0);

    // Arrays to store city and distance information from files.
    std::vector<std::string> userString[81];
    std::string takeLine[81];

    // Read data from the "adjacent_cities.txt" file.
    std::ifstream file("adjacent_cities.txt");

    int i = 0;
    // Read each line from the file and store it in takeLine array.
    while (getline(file, takeLine[i], '\n')) {
        i++;
    }

    size_t commaIndex = 0;
    int r = 0;
    int a = 0;
    // Process each line to extract city information.
    while (a < i) {
        while ((commaIndex = takeLine[a].find(',')) != std::string::npos) {
            userString[a].push_back(takeLine[a].substr(0, commaIndex));
            takeLine[a] = takeLine[a].substr(commaIndex + 1);
        }

        userString[a].push_back(takeLine[a].substr(0, commaIndex));
        takeLine[a] = takeLine[a].substr(commaIndex + 1);
        commaIndex = 0;

        // Increment the vertex count in the graph.
        r = graph.getVertices();
        graph.setVertices(++r);

        a++;
    }

    // Add vertices to the graph using city names.
    for (int i = 0; i < 81; i++) {
        graph.addVertex(userString[i][0]);
    }

    a = 0;
    i = 0;
    std::vector<std::string> userString2[82];
    std::string takeLine2[82];

    // Read data from the "CityDistances.txt" file.
    std::ifstream file2("CityDistances.txt");

    // Read each line from the file and store it in takeLine2 array.
    while (getline(file2, takeLine2[i], '\n')) {
        i++;
    }

    size_t semicolonIndex = 0;
    // Process each line to extract distance information.
    while (a < i) {
        while ((semicolonIndex = takeLine2[a].find(';')) != std::string::npos) {
            userString2[a].push_back(takeLine2[a].substr(0, semicolonIndex));
            takeLine2[a] = takeLine2[a].substr(semicolonIndex + 1);
        }

        userString2[a].push_back(takeLine2[a].substr(0, semicolonIndex));
        takeLine2[a] = takeLine2[a].substr(semicolonIndex + 1);
        semicolonIndex = 0;

        a++;
    }

    int o = 0;
    int k = 1;

    // Populate the graph with edges and distances based on the read data.
    while (o < graph.getVertices()) {
        int j = 0;
        while (j < graph.getVertices()) {
            if (userString[o][k] == userString[j][0]) {
                // Get the distance between two cities.
                int val = graph.takeDistance(o, j, userString2);
                // Add an edge between the cities with the calculated distance.
                graph.addEdge(o, j, val);

                // If all distances for a city are processed, reset k and move to the next city.
                if (userString[o].size() - 1 == k) {
                    k = 1;
                    break;
                }
                k++;
                j = 0;
                continue;
            }
            j++;
        }
        o++;
    }

    // Sort the edges of each vertex in non-decreasing order based on distance.
    graph.sortEdges();

    // Print the graph showing vertices and connected edges.
    graph.printGraph();

    int num = 0;

    // Variables for user interaction.
    std::vector<std::string> cityNames;
    int selectedCityIndex;
    int kClosest;
    char menu;
    int keep = 0;
    do {
        // User menu options.
        std::cout << std::endl << "a. Enter city (or select):" << std::endl << "b. Print selected (or entered) city:" << std::endl << "c. List k closest cities (to selected city)" << std::endl << "d. Find shortest path to...:" << std::endl << "e. Exit:" << std::endl;
        std::cin >> menu;

        // Handle user selection.
        switch (menu) {
        case  'a':
            // User wants to enter or select a city.
            keep = 1;
            enterCity(graph);
            cityNames = graph.getCityNames();
            for (int i = 0; i < 81; i++) {
                if (cityNames[i] == cityName) {
                    selectedCityIndex = i;
                    break;
                }
            }
            break;
        case 'b':
            // User wants to print the selected city.
            printCity();
            break;
        case 'c':
            // User wants to list k closest cities to the selected city.
            if (keep == 1) {
                std::cout << "How many cities do you want to see the shortest route to? Please Enter ";
                std::cin >> kClosest;
                // Check if the requested number of cities is within bounds.
                if (cityNames[selectedCityIndex + 1].size() < kClosest) {
                    std::cout << "Too many cities requested" << std::endl;
                    break;
                }
                // Print the k closest cities.
                graph.printKClosestCities(selectedCityIndex, kClosest);
            }
            else if (keep == 0) {
                std::cout << "First, you have to enter a new city" << std::endl;
            }
            keep = 0;
            break;
        case 'd':
            // User wants to find the shortest path to a destination city.
            std::cout << "Where do you want to go? Enter destination city: ";
            std::cin >> destinationCity;
            destinationCity = fixCityName(destinationCity);
            // Perform Dijkstra's algorithm to find the shortest path.
            num = graph.dijkstra(cityName, destinationCity);
            if (num == 0) {
                std::cout << "Wrong city name. Please enter again" << std::endl;
            }
            break;
        case 'e':
            // User wants to exit the program.
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            // Invalid input from the user.
            std::cout << "Wrong Input. Please enter again" << std::endl;
            break;
        }
    } while (menu != 'e');

    return 0;
}

// Function to enter a city name.
void enterCity(Graph& graph) {
    std::cout << "Enter city name: ";
    std::cin >> cityName;
}

// Function to print the selected city.
void printCity() {
    std::cout << "Selected city: " << cityName << std::endl;
}
