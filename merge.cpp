#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
using namespace std;

// Sequential Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void sequentialMergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    sequentialMergeSort(arr, l, m);
    sequentialMergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        parallelMergeSort(arr, l, m);
        #pragma omp section
        parallelMergeSort(arr, m + 1, r);
    }
    merge(arr, l, m, r);
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

    // Measure time for sequential merge sort
    double seqStart = omp_get_wtime();
    sequentialMergeSort(arr, 0, n - 1);
    double seqEnd = omp_get_wtime();
    double seqTime = seqEnd - seqStart;
    cout<<"Sorted Array"<<endl;
    for(auto x:arr){cout<<x<<" ";}
    cout<<endl;
    cout << "Sequential Merge Sort Time: " << seqTime << " seconds\n";

    // Copy array for parallel merge sort
    vector<int> arr_parallel = arr;

    // Measure time for parallel merge sort
    double parallelStart = omp_get_wtime();
    parallelMergeSort(arr_parallel, 0, n - 1);
    double parallelEnd = omp_get_wtime();
    double parallelTime = parallelEnd - parallelStart;

    cout << "Parallel Merge Sort Time: " << parallelTime << " seconds\n";

    return 0;
}

