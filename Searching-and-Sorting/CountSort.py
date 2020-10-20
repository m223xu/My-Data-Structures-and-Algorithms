## array A of size n, R base numbers,
## index of digit by which we want to sort: d
## (d=0 means sort the least significant digit)
## countSort will modify A
## time: O(n+R) space: O(n+R)

def countSort(A, R, d):
    count = [0] * R
    n = len(A)
    for i in range(n):
        digit = A[i]//pow(R,d)%R
        count[digit] = count[digit] + 1
    
    idx = [0] * R
    for i in range(1, R):
        idx[i] = idx[i-1] + count[i-1]
    
    aux = [0] * n
    for i in range(n):
        digit = A[i]//pow(R,d)%R
        aux[idx[digit]] = A[i]
        idx[digit] = idx[digit] + 1
    
    A[:] = aux

