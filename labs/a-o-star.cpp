#include <bits/stdc++.h>
using namespace std;

struct Node {
    string name;
    bool isAnd; 
    vector<vector<pair<Node*, int>>> children; 
    
    int heuristic;
    int cost;
    bool solved;

    Node(string n, bool isAndNode, int h) {
        name = n;
        isAnd = isAndNode;
        heuristic = h;
        cost = h;
        solved = false;
    }
};

void AOStar(Node* node) {
    if (node->solved) return;

    // ✅ If the node has no children, it's a leaf node
    if (node->children.empty()) {
        node->cost = node->heuristic;
        node->solved = true;
        cout << "Expanding " << node->name << " (leaf) with cost = " << node->cost << endl;
        return;
    }

    int bestCost = INT_MAX;
    vector<pair<Node*, int>> bestChildSet;

    for (auto& childSet : node->children) {
        int setCost = 0;
        for (auto& child : childSet) {
            setCost += child.second + child.first->heuristic;
        }
        if (setCost < bestCost) {
            bestCost = setCost;
            bestChildSet = childSet;
        }
    }

    node->cost = bestCost;
    node->solved = true;

    cout << "Expanding " << node->name << " with cost = " << node->cost << endl;

    for (auto& child : bestChildSet) {
        AOStar(child.first);
    }
}

int main() {
    Node* A = new Node("A", false, 5);
    Node* B = new Node("B", true, 3); 
    Node* C = new Node("C", false, 2); 
    Node* D = new Node("D", false, 4);
    Node* E = new Node("E", false, 1);

    A->children.push_back({{B, 1}});
    A->children.push_back({{C, 1}});
    B->children.push_back({{D, 1}, {E, 1}});

    AOStar(A);

    cout << "Final cost of A = " << A->cost << endl;
    return 0;
}
