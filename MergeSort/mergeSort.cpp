#include <bits/stdc++.h>

using namespace std;

char *printArray(int *arr, int n, int start = 0)
{
    cout << "[";
    for (int i = start; i < start + n; i++)
        cout << arr[i] << (i == start + n - 1 ? "" : ", ");
    cout << "]";
    return (char *)("");
}

void merge(int *L, int length, int firstIdx, int middleIdx, int lastIdx)
{
    int tempArr[length] = {0};
    int i0 = firstIdx, i1 = middleIdx + 1;
    for (int j = firstIdx; j < lastIdx + 1; j++)
        tempArr[j] = (i0 < middleIdx + 1 && (i1 >= lastIdx + 1 || L[i0] <= L[i1])) ? L[i0++] : L[i1++];
    for (int j = firstIdx; j < lastIdx + 1; j++)
        L[j] = tempArr[j];
}

void mergeSort(int *L, int firstIdx, int lastIdx, int length)
{
    if (firstIdx >= lastIdx)
        return;
    int mid = (firstIdx + lastIdx) / 2;
    mergeSort(L, firstIdx, mid, length);
    mergeSort(L, mid + 1, lastIdx, length);
    merge(L, length, firstIdx, mid, lastIdx);
}

int main()
{
    // Randomise the array
    srand(time(0));
    int numOfElements = 17;
    int randomArray[numOfElements];
    int lowerBound = -1000, upperBound = 1000;
    for (int i = 0; i < numOfElements; i++)
        randomArray[i] = rand() % (upperBound - lowerBound + 1) + lowerBound;
    cout << "Original array: " << printArray(randomArray, numOfElements) << endl;
    mergeSort(randomArray, 0, numOfElements - 1, numOfElements);
    cout << "After sort:     " << printArray(randomArray, numOfElements) << endl;
}