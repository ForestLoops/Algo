#include <iostream>
#include <map>
#include <vector>
using namespace std;

class STnode {
public:
    int start, end;
    map<char, STnode*> children;
    bool isTerminal;

    STnode(int start, int end) : start(start), end(end), isTerminal(false) {}
};

class SuffixTree {
public:
    STnode* root;
    string text;

    SuffixTree(const string& text) : text(text) {
        root = new STnode(-1, -1);
        buildSuffixTree();
    }

    void insertSuffix(int suffixStart) {
        STnode* current = root;
        for (int textIndex = suffixStart; textIndex < text.size();) {
            char currentChar = text[textIndex];
            if (current->children.find(currentChar) == current->children.end()) {
                current->children[currentChar] = new STnode(textIndex, text.size() - 1);
                current->children[currentChar]->isTerminal = true;
                return;
            }

            STnode* child = current->children[currentChar];
            int childStart = child->start, i = childStart;

            while (i <= child->end && textIndex < text.size() && text[i] == text[textIndex]) {
                i++; textIndex++;
            }

            if (i > child->end) {
                current = child;
            } else {
                STnode* splitNode = new STnode(childStart, i - 1);
                current->children[currentChar] = splitNode;
                child->start = i;
                splitNode->children[text[i]] = child;
                splitNode->children[text[textIndex]] = new STnode(textIndex, text.size() - 1);
                splitNode->children[text[textIndex]]->isTerminal = true;
                return;
            }
        }
        current->isTerminal = true;
    }

    void buildSuffixTree() {
        for (int i = 0; i < text.size(); i++) {
            insertSuffix(i);
        }
    }

    bool search(const string& query) {
        STnode* current = root;
        for (int queryIndex = 0; queryIndex < query.size();) {
            char currentChar = query[queryIndex];
            if (current->children.find(currentChar) == current->children.end()) {
                return false;
            }

            STnode* child = current->children[currentChar];
            int i = child->start;

            while (i <= child->end && queryIndex < query.size() && text[i] == query[queryIndex]) {
                i++; queryIndex++;
            }

            if (queryIndex == query.size()) {
                return true;
            }

            if (i <= child->end) {
                return false;
            }

            current = child;
        }

        return true;
    }
};

int main() {
    string data;
    cout << "Enter the string to build the suffix tree: ";
    cin >> data;

    SuffixTree tree(data);

    cout << "\nSuffixes of '" << data << "':\n";
    for (int i = 0; i < data.size(); ++i) {
        cout << data.substr(i) << endl;
    }

    int numQueries;
    cout << "Enter the number of queries: ";
    cin >> numQueries;

    for (int i = 0; i < numQueries; ++i) {
        string query;
        cout << "Enter the query: ";
        cin >> query;

        if (tree.search(query)) {
            cout << "'" << query << "' exists in the suffix tree.\n";
        } else {
            cout << "'" << query << "' does not exist in the suffix tree.\n";
        }
    }

    return 0;
}
