## array A of size n, R base numbers, m digits
## LSD radix sort starts sorting from the least significant digit
## instead of the most significant digit, so that less space is used.
## We can also use other auxilliary digit sorting algorithm, but it must be stable.
## time: O(m(n+R)) space: O(n+R)

import CountSort

def lsdRadixSort(A, R, m):
    for d in range(m):
        countSort(A, R, d)


arr = [32,13,54,40,37,21,10]
lsdRadixSort(arr, 10, 2)
print(arr)
