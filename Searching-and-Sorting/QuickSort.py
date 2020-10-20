## if all the elements are the same, running time becomes O(n^2)
## T(n) = T(k) + T(n-k-1) + O(n)
## average running time O(nlogn), best case O(nlogn)
## in-place algorithm, but not stable

import random

def quickSort(A, low, high):
    ## if we always pick the last element as pivot,
    ## the running time will be O(n^2) if the given array is already sorted
    def partition():
        pivot = high
        i = low   ## i is the index that all elements before it are less than A[pivot]
        for j in range(low, high): ## all the elements before pivot
            if (A[j] < A[pivot]):
                A[i], A[j] = A[j], A[i]
                i = i + 1
        A[i], A[pivot] = A[pivot], A[i]
        return i

    if (high <= low):
        return
    pivot = partition()
    quickSort(A, low, pivot-1)
    quickSort(A, pivot+1, high)
    return
    


## expected running time is O(nlogn)

def randomizedQuickSort(A, low, high):
    ## randomly pick an element as pivot and do partition
    def randomizedPartition():
        pivot = random.randint(low, high)
        A[pivot], A[high] = A[high], A[pivot]
        pivot = high
        i = low
        for j in range(low, high):
            if (A[j] < A[pivot]):
                A[i], A[j] = A[j], A[i]
                i = i + 1
        A[i], A[pivot] = A[pivot], A[i]
        return i
        
    if (high <= low):
        return
    pivot = randomizedPartition()
    randomizedQuickSort(A, low, pivot-1)
    randomizedQuickSort(A, pivot+1, high)
    return



arr1 = [6,5,87,2,9,4,3,4,6,8]
randomizedQuickSort(arr1,0,9)
print(arr1)
arr2 = [3,2,2,2,2,2,2]
randomizedQuickSort(arr2,0,6)
print(arr2)
