#include <bits/stdc++.h>
using namespace std;

class AVLTree {
    struct Node {
        int id;
        string name;
        Node *left, *right;
        int height;

        Node(int id, string name) : id(id), name(name), left(NULL), right(NULL), height(1) {}
    };

    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int id, string name) {
        if (!node) return new Node(id, name);
        if (id < node->id) node->left = insert(node->left, id, name);
        else if (id > node->id) node->right = insert(node->right, id, name);
        else return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);
        if (balance > 1 && id < node->left->id) return rotateRight(node);
        if (balance < -1 && id > node->right->id) return rotateLeft(node);
        if (balance > 1 && id > node->left->id) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && id < node->right->id) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << "ID: " << node->id << " Name: " << node->name << endl;
        inOrder(node->right);
    }

public:
    AVLTree() : root(NULL) {}

    void addPatient(int id, string name) {
        root = insert(root, id, name);
    }

    void display() {
        inOrder(root);
    }
};

int main() {
    AVLTree hospital;
    hospital.addPatient(101, "Alice");
    hospital.addPatient(105, "Bob");
    hospital.addPatient(103, "Charlie");

    cout << "Patient Records:\n";
    hospital.display();

    return 0;
}
