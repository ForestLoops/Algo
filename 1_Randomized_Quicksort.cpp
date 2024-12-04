#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void quick_sort(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    srand(time(nullptr));
    int pivot_index = left + rand() % (right - left + 1);
    int pivot = arr[pivot_index], i = left;
    swap(arr[pivot_index], arr[right]);
    for (int j = left; j < right; ++j)
        if (arr[j] < pivot)
            swap(arr[i++], arr[j]);
    swap(arr[i], arr[right]);

    quick_sort(arr, left, i - 1);
    quick_sort(arr, i + 1, right);
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quick_sort(arr, 0, arr.size() - 1);

    cout << "Sorted array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
