#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    double bandwidth;
};

struct Node {
    int id;
    vector<Edge> edges;
};

class RoutingEngine {
private:
    vector<unique_ptr<Node>> nodes;
    int numNodes;

public:
    RoutingEngine(int n) : numNodes(n) {
        for (int i = 0; i < n; i++) {
            nodes.push_back(make_unique<Node>());
            nodes[i]->id = i;
        }
    }

    void addEdge(int from, int to, double bw) {
        if (from >= 0 && from < numNodes) {
            nodes[from]->edges.push_back({to, bw});
        }
    }

    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;
        int u, v;
        double bw;
        while (file >> u >> v >> bw) {
            addEdge(u, v, bw);
        }
        return true;
    }

    bool dfsPath(int curr, int dest, double minBW, vector<bool>& visited, vector<int>& path) {
        visited[curr] = true;
        path.push_back(curr);

        if (curr == dest) return true;

        for (const auto& edge : nodes[curr]->edges) {
            if (edge.bandwidth >= minBW && !visited[edge.to]) {
                if (dfsPath(edge.to, dest, minBW, visited, path)) return true;
            }
        }

        path.pop_back(); // This is the "backtracking" step
        return false;
    }

    vector<int> findPath(int src, int dst, double minBW) {
        vector<bool> visited(numNodes, false);
        vector<int> path;
        if (dfsPath(src, dst, minBW, visited, path)) return path;
        return {};
    }
};

int main() {
    RoutingEngine engine(6);
    if (!engine.loadFromFile("network.txt")) {
        cout << "File not found!" << endl;
        return 1;
    }

    vector<int> result = engine.findPath(0, 5, 70.0);
    if (!result.empty()) {
        cout << "Path: ";
        for (int n : result) cout << n << " ";
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }
    return 0;
}

