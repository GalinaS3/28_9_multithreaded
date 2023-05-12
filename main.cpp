#include <iostream>
#include<future>
#include <chrono>
#include <random>


void merge(int* arr, int l, int m, int r)
{
    int nl = m - l + 1;
    int nr = r - m;

    int* left = new int[nl];
    int* right = new int[nr];
    
    for (int i = 0; i < nl; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0;
    int k = l;  

    while (i < nl && j < nr) {
        
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    while (i < nl) {
        arr[k] = left[i];
        i++;
        k++;
    }
    
    while (j < nr) {
        arr[k] = right[j];
        j++;
        k++;
    }
    delete[] left;
    delete[] right;
}

void mergeSort(int* arr, int l, int r)
{
    int m;
    if (l < r) {
        
        m = (l + r) / 2;
        if (m - l > 10000) {
            std::future <void> f = std::async(std::launch::async, mergeSort, arr, l, m);
            mergeSort(arr, m + 1, r);
            f.get();
            merge(arr, l, m, r);
        }
        else
        {
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r); 
            merge(arr, l, m, r);
        }
    }
}

int main()
{
    srand(0);
    long n = 10000000;
    int* array = new int[n];
    for (long i = 0; i < n; i++) {
        array[i] = rand() % 5000;
    }

    time_t start, end;
   
    time(&start);
    mergeSort(array, 0, n - 1);
    time(&end);

    double seconds = difftime(end, start);
    printf("The time: %f seconds\n", seconds);

    for (long i = 0; i < n-1; i++) {
        if (array[i] > array[i + 1]) {
            std::cout << "Unsorted" << std::endl;
            break;
        }
        if (i = n - 1)
            std::cout << "Sorted OK" << std::endl;
    }
    
    delete[] array;
    return 0;
        
}