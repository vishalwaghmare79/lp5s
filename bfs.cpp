#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    Node* left;
    Node* right;
    int data;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BreadthFS {
public:
    Node* insert(Node* root, int data);
    void bfs(Node* root);
};

Node* BreadthFS::insert(Node* root, int data) {
    if (!root) {
        return new Node(data);
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (!current->left) {
            current->left = new Node(data);
            break;
        } else {
            q.push(current->left);
        }

        if (!current->right) {
            current->right = new Node(data);
            break;
        } else {
            q.push(current->right);
        }
    }

    return root;
}

void BreadthFS::bfs(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int qSize = q.size();

        #pragma omp parallel for
        for (int i = 0; i < qSize; i++) {
            Node* currNode;

            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << currNode->data << " ";
            }

            if (currNode->left) {
                q.push(currNode->left);
            }

            if (currNode->right) {
                q.push(currNode->right);
            }
        }
    }

    cout << endl;
}

int main() {
    BreadthFS treeOps;
    Node* root = nullptr;
    int data;
    char ans;

    do {
        cout << "Enter data to insert into tree: ";
        cin >> data;

        root = treeOps.insert(root, data);

        cout << "Do you want to insert another node? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    cout << "Breadth-First Search output: ";
    treeOps.bfs(root);

    return 0;
}
