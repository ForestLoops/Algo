#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int randomisedSelect(vector<int> &arr, int left, int right, int k)
{
    if (left == right)
        return arr[left];
    srand(time(nullptr));
    int pivot_index = left + rand() % (right - left + 1);
    swap(arr[pivot_index], arr[right]);
    int pivot = arr[right], i = left;
    for (int j = left; j < right; j++)
        if (arr[j] < pivot)
            swap(arr[i++], arr[j]);
    swap(arr[i], arr[right]);

    if (k == i)
        return arr[k];
    return k < i ? randomisedSelect(arr, left, i - 1, k) : randomisedSelect(arr, i + 1, right, k);
}

int main()
{
    int n, k;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter the value of i (1 <= i <= " << n << "): ";
    cin >> k;

    if (k <= 0 || k > n) {
        cout << "Invalid value of k!" << endl;
        return 1;
    }

    cout << "The " << k << "th smallest element is: " << randomisedSelect(arr, 0, arr.size() - 1, k - 1) << endl;

    return 0;
}