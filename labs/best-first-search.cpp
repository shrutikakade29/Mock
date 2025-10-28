#include <bits/stdc++.h>
using namespace std;

struct Node {
    int vertex;
    int h; 

    bool operator>(const Node& other) const {
        return h > other.h; 
    }
};

void bestFirstSearch(int start, int goal, vector<vector<pair<int,int>>>& adj, vector<int>& heuristic) {
    int V = adj.size();
    vector<bool> visited(V, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, heuristic[start]});

    cout << "Best-First Search Path: ";

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int node = current.vertex;

        if (visited[node]) continue;
        visited[node] = true;

        cout << node << " ";

        if (node == goal) {
            cout << "\nGoal reached!" << endl;
            return;
        }

        for (auto [neighbor, cost] : adj[node]) {
            if (!visited[neighbor]) {
                pq.push({neighbor, heuristic[neighbor]});
            }
        }
    }
    cout << "\nGoal not reachable." << endl;
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
    bestFirstSearch(start, goal, adj, heuristic);

    return 0;
}
