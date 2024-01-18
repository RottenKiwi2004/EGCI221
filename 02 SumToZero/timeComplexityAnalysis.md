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

$$T(n) = T(\frac n 2) + T(\frac n 2) + n = 2T(\frac n 2) + n$$

Let $2^k = n$

Backward substitution:

$$T(2^k) = 2\left(2T(2^{k-1}) + n\right) + n$$

$$T(2^k) = 2\left(2\left(2\left(2T(2^{k-2}) + n\right) + n\right) + n\right) + n$$

$$\vdots$$

$$T(2^k) = nk + 2^k$$

Since $2^k = n, k = \log n$

Therefore,

$$T(n) = n \log n + n = O(n \log n)$$
