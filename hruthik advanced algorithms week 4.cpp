#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

// First reverse function implementation using iteration
vector<int> reverse(vector<int> vec) {
    int left = 0;
    int right = vec.size() - 1;
    while (left < right) {
        int temp = vec[left];
        vec[left] = vec[right];
        vec[right] = temp;
        left++;
        right--;
    }
    return vec;
}

// Alternative reverse function using recursion
vector<int> reverseRecursive(vector<int> vec, int start, int end) {
    if (start >= end) {
        return vec;
    }
    swap(vec[start], vec[end]);
    return reverseRecursive(vec, start + 1, end - 1);
}

class Graph {
private:
    map<int, map<int, int>> graph;  // adjacency map: source -> {destination -> weight}
    set<int> vertices;

public:
    // Add an edge to the graph
    void addEdge(int source, int dest, int weight) {
        graph[source][dest] = weight;
        vertices.insert(source);
        vertices.insert(dest);
    }

    // Get number of vertices
    int getVertexCount() {
        return vertices.size();
    }

    // Find shortest path using Dijkstra's algorithm
    pair<vector<int>, int> findShortestPath(int start, int end) {
        // Initialize distances and previous nodes
        map<int, int> distances;
        map<int, int> previous;
        set<int> unvisited;

        // Set initial distances to infinity
        for (int vertex : vertices) {
            distances[vertex] = numeric_limits<int>::max();
            unvisited.insert(vertex);
        }
        distances[start] = 0;

        while (!unvisited.empty()) {
            // Find unvisited vertex with minimum distance
            int current = -1;
            int minDist = numeric_limits<int>::max();
            for (int vertex : unvisited) {
                if (distances[vertex] < minDist) {
                    current = vertex;
                    minDist = distances[vertex];
                }
            }

            if (current == -1 || current == end) {
                break;
            }

            unvisited.erase(current);

            // Update distances to neighbors
            for (const auto& neighbor : graph[current]) {
                int dest = neighbor.first;
                int weight = neighbor.second;

                if (unvisited.find(dest) != unvisited.end()) {
                    int newDist = distances[current] + weight;
                    if (newDist < distances[dest]) {
                        distances[dest] = newDist;
                        previous[dest] = current;
                    }
                }
            }
        }

        // Reconstruct path
        vector<int> path;
        if (distances[end] != numeric_limits<int>::max()) {
            int current = end;
            while (current != start) {
                path.push_back(current);
                current = previous[current];
            }
            path.push_back(start);
            
            // Use the reverse function as required
            path = reverse(path);
        }

        return {path, distances[end]};
    }
};

// Function to print the path
void printPath(const vector<int>& path, int distance) {
    if (path.empty()) {
        cout << "No path exists!" << endl;
        return;
    }

    cout << "Shortest distance: " << distance << endl;
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

int main() {
    Graph g;

    // Create a different example graph
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, 1);
    g.addEdge(3, 5, 3);
    g.addEdge(4, 5, 2);

    cout << "Welcome to Shortest Path Finder!" << endl;
    cout << "Available nodes: 0 to 5" << endl;

    int start, end;
    bool validInput = false;

    do {
        cout << "\nEnter starting node (0-5): ";
        cin >> start;
        cout << "Enter destination node (0-5): ";
        cin >> end;

        if (start >= 0 && start <= 5 && end >= 0 && end <= 5) {
            validInput = true;
        } else {
            cout << "Invalid input! Please enter nodes between 0 and 5." << endl;
        }
    } while (!validInput);

    // Find and print the shortest path
    auto result = g.findShortestPath(start, end);
    vector<int> path = result.first;
    int distance = result.second;

    cout << "\nResults:" << endl;
    printPath(path, distance);

    // Demonstrate both reverse functions work
    cout << "\nDemonstrating both reverse functions:" << endl;
    cout << "Original path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Iterative reverse: ";
    vector<int> iterReversed = reverse(path);
    for (int node : iterReversed) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Recursive reverse: ";
    vector<int> recReversed = reverseRecursive(path, 0, path.size() - 1);
    for (int node : recReversed) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}