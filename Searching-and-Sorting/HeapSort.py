## time: O(nlogn), space: O(1) (in-place)
## unstable, usually slower than quicksort since more swappings



def heapSort(A):
    def heapify(A, n, i):
        ## heapify tree from element i, assuming the subtrees are heapified
        left = 2*i+1
        right = 2*i+2
        largest = i
        if (left < n and A[left] > A[i]):
            largest = left
        if (right < n and A[right] > A[largest]):
            largest = right
        if (largest != i):
            A[i], A[largest] = A[largest], A[i]
            heapify (A, n, largest)


    n = len(A)
    ## find the parent of the last element
    end = n // 2 - 1
    
    ## the following two lines builds a max heap, taking O(n) time.
    for i in range(end, -1, -1):
        heapify(A, n, i)
    
    ## extract max from the heap, put it at the back, repeat until there is only one element
    ## it will take O(nlogn) time
    for i in range(n-1, 0, -1):
        A[0], A[i] = A[i], A[0]
        n = n - 1
        heapify(A, n, 0)
    

if __name__ == "__main__":
    arr = [4,5,1,75,12,3,0,-3,5,75,10]
    heapSort(arr)
    print(arr)

