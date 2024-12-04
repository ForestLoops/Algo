#include <iostream>
using namespace std;

class BTreeNode {
    int* keys;
    BTreeNode** children;
    int t, n;
    bool isLeaf;

public:
    BTreeNode(int t, bool isLeaf);
    void traverse();
    BTreeNode* search(int key);
    void insertNonFull(int key);
    void splitChild(int i, BTreeNode* y);
    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;

public:
    BTree(int t) : root(nullptr), t(t) {}
    void traverse() { if (root) root->traverse(); }
    BTreeNode* search(int key) { return root ? root->search(key) : nullptr; }
    void insert(int key);
};

BTreeNode::BTreeNode(int t1, bool isLeaf1) : t(t1), isLeaf(isLeaf1), n(0) {
    keys = new int[2 * t - 1];
    children = new BTreeNode*[2 * t];
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; ++i) {
        if (!isLeaf) children[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!isLeaf) children[i]->traverse();
}

BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < n && key > keys[i]) ++i;
    if (keys[i] == key) return this;
    return isLeaf ? nullptr : children[i]->search(key);
}

void BTree::insert(int key) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = key;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode* newRoot = new BTreeNode(t, false);
            newRoot->children[0] = root;
            newRoot->splitChild(0, root);
            int i = (newRoot->keys[0] < key) ? 1 : 0;
            newRoot->children[i]->insertNonFull(key);
            root = newRoot;
        } else {
            root->insertNonFull(key);
        }
    }
}

void BTreeNode::insertNonFull(int key) {
    int i = n - 1;
    if (isLeaf) {
        while (i >= 0 && keys[i] > key) { keys[i + 1] = keys[i]; --i; }
        keys[i + 1] = key;
        ++n;
    } else {
        while (i >= 0 && keys[i] > key) --i;
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < key) ++i;
        }
        children[i + 1]->insertNonFull(key);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; ++j) z->keys[j] = y->keys[j + t];
    if (!y->isLeaf) for (int j = 0; j < t; ++j) z->children[j] = y->children[j + t];
    y->n = t - 1;
    for (int j = n; j >= i + 1; --j) children[j + 1] = children[j];
    children[i + 1] = z;
    for (int j = n - 1; j >= i; --j) keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    ++n;
}

int main() {
    int t;
    cout << "Enter minimum degree of B-Tree: ";
    cin >> t;
    BTree bTree(t);

    int choice, key;
    do {
        cout << "\n1. Insert\n2. Traverse\n3. Search\n4. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Enter key to insert: "; cin >> key; bTree.insert(key); break;
            case 2: cout << "Tree traversal: "; bTree.traverse(); cout << endl; break;
            case 3: cout << "Enter key to search: "; cin >> key; 
                    cout << (bTree.search(key) ? "Found" : "Not found") << endl; break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 4);
    return 0;
}
