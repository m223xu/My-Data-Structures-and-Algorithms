def jumpSearch(arr, x):
    ## array must be sorted
    n = len(arr)
    size = int(math.sqrt(n))
    bound = 0
    while (bound < n):
        if (arr[bound] == x):
            return bound
        elif (arr[bound] < x):
            bound = bound + size
        else:
            break
    start = bound - size
    end = bound
    if (end == 0):
        return None
    if (end >= n):
        end = n - 1
    for i in range(start, end+1):
        if (arr[i] == x):
            return i
    return None
