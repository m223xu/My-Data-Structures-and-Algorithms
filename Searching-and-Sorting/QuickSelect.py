## quick select returns the kth smallest element, k ranges from 0 to n-1
## average running time O(n), worst case O(n^2), best case O(n)
## side effect: modify the original array


def quickSelect(A, low, high, k):
    def partition():
        pivot = high
        i = low   ## i is the index that all elements before it are less than A[pivot]
        for j in range(low, high):
            if (A[j] < A[pivot]):
                A[i], A[j] = A[j], A[i]
                i = i + 1
        A[i], A[pivot] = A[pivot], A[i]
        return i

    pivot = partition()
    if (k == pivot):
        return A[pivot]
    elif (k < pivot):
        return quickSelect(A, low, pivot-1, k)
    else:
        return quickSelect(A, pivot+1, high, k)

import random

def randomizedQuickSelect(A, low, high, k):
    def randomizedPartition():
        pivot = random.randint(low, high)
        A[pivot], A[high] = A[high], A[pivot]
        pivot = high
        i = low   ## i is the index that all elements before it are less than A[pivot]
        for j in range(low, high):
            if (A[j] < A[pivot]):
                A[i], A[j] = A[j], A[i]
                i = i + 1
        A[i], A[pivot] = A[pivot], A[i]
        return i

    pivot = randomizedPartition()
    if (k == pivot):
        return A[pivot]
    elif (k < pivot):
        return randomizedQuickSelect(A, low, pivot-1, k)
    else:
        return randomizedQuickSelect(A, pivot+1, high, k)

import math

## assume that all the elements are different, 
## then this algorithm will cost O(n) even at the worst case.
def improvedQuickSelect(A, low, high, k):
    """ 
    The following way of partition will eliminate the possibility of extreme pivot.
    There will be at least "k/2 * (ceil(1/2 * ceil(n/k)) - 2)" elements 
    less than the pivot, which is at least "n/4 - k".
    The improvedPartition costs "T(ceil(n/k)) + O(n)".

    Here we choose k=5. Actually any value greater than 4 is fine.
    find pivot: T(ceil(n/5))
    worst case recursive call: T(7n/10+6)
    get medians and do partition: O(n)

    T(n) <= T(ceil(n/5)) + T(7n/10+6) + O(n)
    Finally, T(n) = O(n)
    """
    def improvedPartition():
        def sort(A, low, high):
            ## sort A partially
            for i in range(low, high):
                min = i
                for j in range(i+1, high+1):
                    if (A[j] < A[min]):
                        min = j
                A[min], A[i] = A[i], A[min]


        ## divide the array to ceil(n/5) groups
        ## for each group, sort numbers in it and get the median of each group, taking O(n) time
        n = high - low + 1
        nB = int(math.ceil(n/5))
        B = [0 for x in range(nB)]
        for i in range(n//5):
            sort(A, low+5*i, low+5*i+4)
            B[i] = A[low+5*i+2]
        if (n % 5 != 0):
            sort(A, low+n//5*5, high)
            B[n//5] = A[low+n//5*5+(n%5+1)//2-1]

        ## find the median of array B, that is, the median of median of each group, taking T(ceil(n/5)) time
        mid = (nB+1) // 2 - 1
        median = improvedQuickSelect(B, 0, nB-1, mid)

        ## the median is the pivot, so find the index of the median in A, and do partition in A, taking O(n) time
        pivot = low
        while (A[pivot] != median):
            pivot = pivot + 1

        A[pivot], A[high] = A[high], A[pivot]
        pivot = high
        i = low
        for j in range(low, high):
            if (A[j] < A[pivot]):
                A[i], A[j] = A[j], A[i]
                i = i + 1
        A[i], A[pivot] = A[pivot], A[i]
        return i

    if (low == high):
        return A[low]
    pivot = improvedPartition()
    if (k == pivot):
        return A[pivot]
    elif (k < pivot):
        return improvedQuickSelect(A, low, pivot-1, k)
    else:
        return improvedQuickSelect(A, pivot+1, high, k)




arr1 = [61,100,87,2,9,4,3,79,6,8,11,10,0,-3]
print(improvedQuickSelect(arr1, 0, 13, 5))
print(arr1)


