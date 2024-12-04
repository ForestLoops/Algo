#include <iostream>
using namespace std;

struct TreeNode {
    int key;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int value) : key(value) {}
};

class BinaryTree {
private:
    TreeNode* root = nullptr;

    TreeNode* insert(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        return node;
    }

    bool search(TreeNode* node, int key) {
        if (!node) return false;
        if (key == node->key) return true;
        return key < node->key ? search(node->left, key) : search(node->right, key);
    }

    void inOrderTraversal(TreeNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->key << " ";
            inOrderTraversal(node->right);
        }
    }

public:
    void insert(int key) { root = insert(root, key); }
    bool search(int key) { return search(root, key); }
    void display() { inOrderTraversal(root); cout << endl; }
};

int main() {
    BinaryTree tree;
    int choice, key;

    do {
        cout << "\n1. Insert\n2. Search\n3. Display\n4. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter the key to insert: ";
            cin >> key;
            tree.insert(key);
            cout << "Key " << key << " inserted.\n";
            break;
        case 2:
            cout << "Enter the key to search: ";
            cin >> key;
            cout << (tree.search(key) ? "Found" : "Not found") << " in the tree.\n";
            break;
        case 3:
            cout << "In-order traversal: ";
            tree.display();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
