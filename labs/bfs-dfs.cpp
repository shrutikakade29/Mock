#include <bits/stdc++.h>
using namespace std;

bool BFS(int start, int goal, vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<int> parent(V, -1); // to reconstruct path
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == goal) { // Goal found
            cout << "Goal found using BFS!\nPath: ";
            vector<int> path;
            for (int v = goal; v != -1; v = parent[v])
                path.push_back(v);
            reverse(path.begin(), path.end());
            for (int v : path) cout << v << " ";
            cout << endl;
            return true;
        }

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = node;
                q.push(neighbor);
            }
        }
    }
    return false; // Goal not found
}

bool DFSUtil(int node, int goal, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& path) {
    visited[node] = true;
    path.push_back(node);

    if (node == goal) {
        cout << "Goal found using DFS!\nPath: ";
        for (int v : path) cout << v << " ";
        cout << endl;
        return true;
    }

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (DFSUtil(neighbor, goal, adj, visited, path))
                return true; // stop if goal found
        }
    }

    path.pop_back(); // backtrack
    return false;
}

bool DFS(int start, int goal, vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<int> path;
    return DFSUtil(start, goal, adj, visited, path);
}

int main() {
    int V = 7;
    vector<vector<int>> adj(V);

    // Modified graph to clearly show BFS vs DFS difference
    adj[0] = {1, 2};
    adj[1] = {3};
    adj[2] = {4};
    adj[3] = {5};
    adj[4] = {6};
    adj[5] = {6};
    adj[6] = {}; // goal node

    int start = 0, goal = 6;

    BFS(start, goal, adj, V);
    DFS(start, goal, adj, V);

    return 0;
}
