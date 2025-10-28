#include <bits/stdc++.h>
using namespace std;

struct Node {
    int vertex;
    int g;
    int h;
    int f; 

    bool operator>(const Node& other) const {
        return f > other.f; 
    }
};

void AStar(int start, int goal, vector<vector<pair<int,int>>>& adj, vector<int>& heuristic) {
    int V = adj.size();
    vector<int> g(V, INT_MAX);     
    vector<int> parent(V, -1);     
    vector<bool> visited(V, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    g[start] = 0;
    pq.push({start, 0, heuristic[start], heuristic[start]});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int node = current.vertex;

        if (visited[node]) continue;
        visited[node] = true;

        if (node == goal) {
            cout << "Goal reached using A*!\nPath: ";
            vector<int> path;
            for (int v = goal; v != -1; v = parent[v])
                path.push_back(v);
            reverse(path.begin(), path.end());
            for (int v : path) cout << v << " ";
            cout << "\nTotal cost: " << g[goal] << endl;
            return;
        }

        for (auto [neighbor, cost] : adj[node]) {
            int new_g = g[node] + cost;
            if (new_g < g[neighbor]) {
                g[neighbor] = new_g;
                parent[neighbor] = node;
                int f = new_g + heuristic[neighbor];
                pq.push({neighbor, new_g, heuristic[neighbor], f});
            }
        }
    }
    cout << "Goal not reachable." << endl;
}

int main() {
    int V = 6; 
    vector<vector<pair<int,int>>> adj(V);
    adj[0] = {{1, 1}, {2, 1}};
    adj[1] = {{0, 1}, {3, 1}, {4, 1}};
    adj[2] = {{0, 1}, {4, 1}};
    adj[3] = {{1, 1}, {5, 1}};
    adj[4] = {{1, 1}, {2, 1}, {5, 1}};
    adj[5] = {{3, 1}, {4, 1}};

    vector<int> heuristic = {5, 4, 3, 2, 1, 0};

    int start = 0, goal = 5;
    AStar(start, goal, adj, heuristic);

    return 0;
}