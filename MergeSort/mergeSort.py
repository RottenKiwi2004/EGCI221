from random import randint as rand
import math
# testCase = [5, -1, 2, 3, -2]

# Random case
numOfElements = 8
testCase = set()
while len(testCase) <= numOfElements:
    num = rand(-100, 100)
    testCase.add(num)

testCase = list(testCase)

comparisonCount = 0


def merge(L: list[int], firstIndex: int, middleIndex: int, lastIndex: int):
    tempArr = L[::]
    i0 = firstIndex
    i1 = middleIndex
    for j in range(firstIndex, lastIndex):
        global comparisonCount
        comparisonCount += 1
        if i0 < middleIndex and (i1 >= lastIndex or L[i0] <= L[i1]):
            tempArr[j] = L[i0]
            i0 += 1
        else:
            tempArr[j] = L[i1]
            i1 += 1

    print(tempArr)
    print(L)
    print()
    L = tempArr[::]



def mergeSort(L: list[int], firstIndex: int, lastIndex: int):
    if firstIndex < lastIndex:
        mid = (firstIndex + lastIndex) // 2
        mergeSort(L, firstIndex, mid)
        mergeSort(L, mid + 1, lastIndex)
        merge(L, firstIndex, mid, lastIndex)


mergeSort(testCase, 0, numOfElements)
print(f"Comparison count: {comparisonCount}")
print(f"n*log(n): {numOfElements * math.log(numOfElements)}")
print(testCase)
