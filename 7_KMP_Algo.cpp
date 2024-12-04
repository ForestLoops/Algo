#include <iostream>
#include <vector>
#include <string>

using namespace std;

void computeLPSArray(const string& pattern, vector<int>& lps) {
    int length = 0;
    lps[0] = 0;

    for (int i = 1; i < pattern.length(); ) {
        if (pattern[i] == pattern[length]) {
            lps[i++] = ++length;
        } else if (length) {
            length = lps[length - 1];
        } else {
            lps[i++] = 0;
        }
    }
}

void KMPSearch(const string& text, const string& pattern) {
    int n = text.length(), m = pattern.length();
    vector<int> lps(m);

    computeLPSArray(pattern, lps);

    for (int i = 0, j = 0; i < n; ) {
        if (pattern[j] == text[i]) {
            i++; j++;
            if (j == m) {
                cout << "Pattern found at index " << i - j << endl;
                j = lps[j - 1];
            }
        } else if (j) {
            j = lps[j - 1];
        } else {
            i++;
        }
    }
}

int main() {
    string text, pattern;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the pattern to search: ";
    getline(cin, pattern);

    KMPSearch(text, pattern);

    return 0;
}
