import copy


# 2d knapsack problem

def ZeroAndOne(array, m, n):
    # Assume that we have m 0s and n 1s, how many elements at most in the array can we form?
    # Input: array=["10", "0001", "111001", "1", "0"], m=5, n=3   Output: 4
    
    l = len(array)

    oldTable = [[0 for x in range(n+1)] for y in range(m+1)]
    newTable = [[0 for x in range(n+1)] for y in range(m+1)]

    for x in range(1, l+1):
        zeroes = array[x-1].count("0")
        ones = array[x-1].count("1")
        
        oldTable = copy.deepcopy(newTable) ## do a deep copy, "=" will assign the reference
        for y in range(m+1):
            for z in range(n+1):
                if (y >= zeroes and z >= ones):
                    newTable[y][z] = max(oldTable[y-zeroes][z-ones] + 1, oldTable[y][z])
                else:
                    newTable[y][z] = oldTable[y][z]
    return newTable[m][n]

print(ZeroAndOne(["10", "0001", "111001" , "1", "0"], 5, 3))

