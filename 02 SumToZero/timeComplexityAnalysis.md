# Time Complexity Analysis for `sumToZero`

There are three functions related to finding the triplet that sums up to zero. `randomiseArray`, `merge`, and `mergeSort`

### Analysis on `merge()`

```cpp
void merge(int *L, int length, int firstIdx, int middleIdx, int lastIdx)
{
    int tempArr[length] = {0};
    int i0 = firstIdx, i1 = middleIdx + 1;
    for (int j = firstIdx; j < lastIdx + 1; j++)
        tempArr[j] = (i0 < middleIdx + 1 && (i1 >= lastIdx + 1 || L[i0] <= L[i1])) ? L[i0++] : L[i1++];
    for (int j = firstIdx; j < lastIdx + 1; j++)
        L[j] = tempArr[j];
}
```

I will ignore any other operations in this function and focus on the loops.

There are two loops in this function. Both runs from `firstIdx` to `lastIdx + 1`.

The most that both loops can run is when `lastIdx` is `n-1` and `firstIdx` is `0` which is $n+1$ iterations or $O(n)$

Therefore, `merge` function runs at time complexity of $O(n)$

### Analysis on `mergeSort()`

```cpp
void mergeSort(int *L, int firstIdx, int lastIdx, int length)
{
    if (firstIdx >= lastIdx)
        return;
    int mid = (firstIdx + lastIdx) / 2;
    mergeSort(L, firstIdx, mid, length);
    mergeSort(L, mid + 1, lastIdx, length);
    merge(L, length, firstIdx, mid, lastIdx);
}
```

This function is in the form of recursion.

The base case here is when `firstIdx >= lastIdx` or in other words, `n <= 1`.

Again, ignore the other basic operations and focus on the function call.

Let $T(n)$ be the time required to run `mergeSort` with `n` elements.

Because we know that merging is $O(n)$

$$T(n) =  \begin{cases} T(\frac n 2) + T(\frac n 2) + n = 2T(\frac n 2) + n &; n > 1 \\ 1 &; n \leq 1 \end{cases}$$

Let $2^k = n$

Backward substitution:

$$T(2^k) = 2\left(2T(2^{k-1}) + n\right) + n$$

$$T(2^k) = 2\left(2\left(2\left(2T(2^{k-2}) + n\right) + n\right) + n\right) + n$$

$$\vdots$$

$$T(2^k) = nk + 2^k$$

Since $2^k = n, k = \log n$

Therefore,

$$T(n) = n \log n + n = O(n \log n)$$

### Analysis on `sumToZero()`

```cpp
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
```

To find sum of triplets which is equal to zero, we can start by sorting the array.

This will result in an array that at any given index, `i`, for every `lowerIdx <= i`, `L[lowerIdx] <= L[i]`
and for every `i <= higherIdx`, `L[i] <= L[higherIdx]`.

This sorting uses the `mergeSort` function which takes $O(n \log n)$.

Now, loop over the array to pick `i`.
For each `i`, there may or may not be a triplets that satisfies `L[lowerIdx] + L[i] + L[higherIdx] = 0`

So, let `lowerIdx = i - 1` and `higherIdx = i + 1`

There are three possible cases.

1. `L[lowerIdx] + L[i] + L[higherIdx] = 0`

   In this case, just return the value of `[L[lowerIdx], L[i], L[higherIdx]]`

2. `L[lowerIdx] + L[i] + L[higherIdx] < 0`

   This means `higherIdx` is too low, increment `higherIdx`

3. `L[lowerIdx] + L[i] + L[higherIdx] > 0`

   This means `lowerIdx` is too high, decrement `lowerIdx`

If in the end, no triplets sums up to `0`, go to next `i`

If after looping through all `i` in the array, and there is still no triplets that sums up to `0`, then it will finally return `[INT_MAX, INT_MAX, INT_MAX]` which means <u>_not found_</u>

For the nested loop,
outer loop will run for $n-1$ times and inner loop will run at most $(i - 1) + (n - i - 1) = n-2$ times.

So, the time complexity of this nested loop is $(n-2)(n-1) = n^2 - 3n + 2 = O(n^2)$

This concludes the `sumToZero` function's time complexity to be $O(n^2)+O(n \log n) = O(n^2)$
