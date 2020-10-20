def interpolationSearch(arr, x):
    ## array must be sorted
    start = 0
    end = len(arr) - 1
    while (start < end and arr[start] < arr[end] and x >= arr[start] and x <= arr[end]):
        mid = start + (end-start) * (x-arr[start]) // (arr[end]-arr[start])
        if (arr[mid] == x):
            return mid
        elif (arr[mid] < x):
            start = mid + 1
        else:
            end = mid - 1
    if (arr[start] == x) return start
    return None
