# Screw this, python passing by reference is to much of a headache that I feel like I should give up
# See the C++ version

from random import randint as rand
import math

# Randomise Array
numOfElements = 8
testCase = set()
while len(testCase) <= numOfElements:
    num = rand(-100, 100)
    testCase.add(num)

testCase = list(testCase)

comparisonCount = 0


def merge(L: list[int], firstIndex: int, middleIndex: int, lastIndex: int):
    print(f"ID of array L in merge: {id(L)}")
    tempArr = L[::]
    print(f"ID of array tempArr in merge: {id(tempArr)}")
    # print(L[firstIndex:middleIndex+1], L[middleIndex+1:lastIndex+1])
    i0 = firstIndex
    i1 = middleIndex + 1
    for j in range(firstIndex, lastIndex):
        global comparisonCount
        comparisonCount += 1
        # print(L[i0], ",", L[i1], " --> ", end="")
        if i0 < middleIndex + 1 and (i1 >= lastIndex + 1 or L[i0] <= L[i1]):
            tempArr[j] = L[i0]
            i0 += 1
            # print(tempArr[j])
        else:
            tempArr[j] = L[i1]
            i1 += 1
            # print(tempArr[j])

    # print(tempArr)
    # print(L)
    # print()
    L[:] = tempArr[:]

    print(f"ID of array L (final): {id(L)}")


def mergeSort(L: list[int], firstIndex: int, lastIndex: int):
    # print(firstIndex, lastIndex)
    print(f"ID of array in mergeSort function: {id(L)}")
    if firstIndex < lastIndex:
        mid = (firstIndex + lastIndex) // 2
        mergeSort(L, firstIndex, mid)
        mergeSort(L, mid + 1, lastIndex)
        merge(L, firstIndex, mid, lastIndex)


print(f"Original array: {testCase}")
print(f"ID of original array: {id(testCase)}")
mergeSort(testCase, 0, numOfElements-1)
print(f"Comparison count: {comparisonCount}")
print(f"n*log(n): {numOfElements * math.log(numOfElements)}")
print(testCase)
