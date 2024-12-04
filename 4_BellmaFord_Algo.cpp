#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge { int src, dest, weight; };

void bellmanFord(int V, int E, const vector<Edge>& edges, int source) {
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (const auto& edge : edges) {
            if (distance[edge.src] != INT_MAX && distance[edge.src] + edge.weight < distance[edge.dest]) {
                distance[edge.dest] = distance[edge.src] + edge.weight;
            }
        }
    }

    for (const auto& edge : edges) {
        if (distance[edge.src] != INT_MAX && distance[edge.src] + edge.weight < distance[edge.dest]) {
            cout << "Graph contains a negative weight cycle." << endl;
            return;
        }
    }

    cout << "Vertex\tDistance from Source (" << source << ")\n";
    for (int i = 0; i < V; ++i) {
        cout << i << "\t" << (distance[i] == INT_MAX ? "INF" : to_string(distance[i])) << endl;
    }
}

int main() {
    int V, E, source;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (src dest weight):\n";
    for (auto& edge : edges) {
        cin >> edge.src >> edge.dest >> edge.weight;
    }

    cout << "Enter source vertex: ";
    cin >> source;

    bellmanFord(V, E, edges, source);
    return 0;
}
