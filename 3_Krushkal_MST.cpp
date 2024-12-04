#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V;
    vector<Edge> edges;
};

struct Subset {
    int parent, rank;
};

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x), rootY = find(subsets, y);
    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

void kruskalMST(Graph& graph) {
    sort(graph.edges.begin(), graph.edges.end(), [](Edge a, Edge b) { return a.weight < b.weight; });

    Subset* subsets = new Subset[graph.V];
    for (int v = 0; v < graph.V; ++v)
        subsets[v] = {v, 0};

    vector<Edge> result;
    for (auto& edge : graph.edges) {
        int x = find(subsets, edge.src), y = find(subsets, edge.dest);
        if (x != y) {
            result.push_back(edge);
            unionSets(subsets, x, y);
        }
    }

    cout << "Edges in the MST:\n";
    int totalWeight = 0;
    for (auto& edge : result) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total weight: " << totalWeight << endl;

    delete[] subsets;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    Graph graph{V};
    cout << "Enter edges (src dest weight):\n";
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.edges.push_back({src, dest, weight});
    }

    kruskalMST(graph);
    return 0;
}
