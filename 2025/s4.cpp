#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;

struct Edge {
    int to;
    int weight;
    int edgeIndex;
};

struct Node {
    long long cost;
    int vertex;
    int edgeIndex;
};

bool operator>(const Node& a, const Node& b) {
    return a.cost > b.cost;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    vector<vector<Edge>> graph(numVertices + 1);
    vector<int> edgeWeights(numEdges);

    for (int i = 0; i < numEdges; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        
        edgeWeights[i] = weight;
        
        Edge edge1 = {to, weight, i};
        Edge edge2 = {from, weight, i};
        
        graph[from].push_back(edge1);
        graph[to].push_back(edge2);
    }
    
    // Dijkstra's algorithm
    priority_queue<Node, vector<Node>, greater<Node>> minHeap;
    vector<long long> minCost(numEdges + 1, LLONG_MAX);
    vector<bool> visited(numEdges + 1, false);
    
    Node startNode = {0, 1, numEdges};
    minHeap.push(startNode);
    minCost[numEdges] = 0;
    
    while (!minHeap.empty()) {
        Node current = minHeap.top();
        minHeap.pop();
        
        int currentEdgeIndex = current.edgeIndex;
        int currentVertex = current.vertex;
        long long currentCost = current.cost;
        
        if (visited[currentEdgeIndex]) {
            continue;
        }
        
        visited[currentEdgeIndex] = true;
        
        if (currentVertex == numVertices) {
            cout << currentCost << endl;
            return 0;
        }
        
        for (const Edge& edge : graph[currentVertex]) {
            int nextVertex = edge.to;
            int nextEdgeIndex = edge.edgeIndex;
            
            if (visited[nextEdgeIndex]) {
                continue;
            }
            
            int currentEdgeWeight = (currentEdgeIndex == numEdges) ? 0 : edgeWeights[currentEdgeIndex];
            int nextEdgeWeight = edgeWeights[nextEdgeIndex];
            long long costDifference = abs(currentEdgeWeight - nextEdgeWeight);
            long long newTotalCost = currentCost + costDifference;

            if (newTotalCost < minCost[nextEdgeIndex]) {
                minCost[nextEdgeIndex] = newTotalCost;
                Node nextNode = {newTotalCost, nextVertex, nextEdgeIndex};
                minHeap.push(nextNode);
            }
        }
    }
    
    return 0;
}