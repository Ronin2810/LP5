#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
using namespace std;
// Serial Bubble Sort
void serialBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i){
	#pragma omp parallel for
        for (int j = 0; j < n - i - 1; ++j){
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    // Input array from user
    vector<int> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Measure time for serial bubble sort
    double serialStart = omp_get_wtime();
    serialBubbleSort(arr);
    double serialEnd = omp_get_wtime();
    double serialTime = serialEnd - serialStart;
    cout<<"Sorted Array"<<endl;
    for(auto x:arr){cout<<x<<" ";}
    cout<<endl;
    cout << "Serial Bubble Sort Time: " << serialTime << " seconds\n";

    // Measure time for parallel bubble sort
    double parallelStart = omp_get_wtime();
    parallelBubbleSort(arr);
    double parallelEnd = omp_get_wtime();
    double parallelTime = parallelEnd - parallelStart;

    cout << "Parallel Bubble Sort Time: " << parallelTime << " seconds\n";

    return 0;
}

