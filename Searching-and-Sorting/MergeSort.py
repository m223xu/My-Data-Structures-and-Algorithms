## time: O(nlogn), space: O(n) (two recursions occur serial)
## stable, not in-place

def merge(aL, aR):
    nL, nR = len(aL), len(aR)
    aOut = [0 for x in range(nL+nR)]
    iL, iR, iOut = 0, 0, 0
    while iL < nL and iR < nR:
        if aL[iL] <= aR[iR]:
            aOut[iOut] = aL[iL]
            iL += 1
            iOut += 1
        else:
            aOut[iOut] = aR[iR]
            iR += 1
            iOut += 1
    while iL < nL:
        aOut[iOut] = aL[iL]
        iL += 1
        iOut += 1
    while iR < nR:
        aOut[iOut] = aR[iR]
        iR += 1
        iOut += 1
    return aOut



def mergeSort(A):
    n = len(A)
    if n == 1:
        return A
    nL = n//2
    aL = A[:nL]
    aR = A[nL:]
    sL = mergeSort(aL)
    sR = mergeSort(aR)
    return merge(sL, sR)


if __name__ == "__main__":
    A = [4,2,5,7,1,10,15]
    A_sorted = mergeSort(A)
    print(A_sorted)