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

void randomiseArray(int *arr, int numOfElements, int lowerBound, int upperBound)
{
    srand(time(0));
    for (int i = 0; i < numOfElements; i++)
        arr[i] = rand() % (upperBound - lowerBound + 1) + lowerBound;
}

int *sumToZero(int *dataArr, int n)
{
    int *result = new int[3];
    result[0] = result[1] = result[2] = INT_MAX;
    mergeSort(dataArr, 0, n - 1, n);
    cout << "Sorted Array: " << printArray(dataArr, n) << endl;

    bool found = false;
    for (int i = 0; i < n - 1; i++)
    {
        int currentElement = dataArr[i];
        for (int lowerIdx = i - 1, higherIdx = i + 1; lowerIdx >= 0 && higherIdx < n;)
        {
            int sumOfThree = currentElement + dataArr[lowerIdx] + dataArr[higherIdx];
            if (!sumOfThree)
            {
                result[0] = currentElement;
                result[1] = dataArr[lowerIdx];
                result[2] = dataArr[higherIdx];
                return result;
            }
            if (sumOfThree < 0)
                higherIdx++;
            if (sumOfThree > 0)
                lowerIdx++;
        }
    }
    return result;
}

int main()
{
    // Randomise the array
    int numOfElements = 3000;
    int randomArray[numOfElements];
    randomiseArray(randomArray, numOfElements, -1000000, 1000000);
    cout << "       Array: " << printArray(randomArray, numOfElements) << endl;
    int *result = sumToZero(randomArray, numOfElements);
    printArray(result, 3);
}