## Find the minimum number of operations that transform one string to another.


def minDistance(s1, s2) -> int:
    # bottom up dp
    m = len(s1)
    n = len(s2)
    table = [[0 for x in range(n+1)] for y in range(m+1)]
    
    for i in range(1, m+1):
        table[i][0] = i

    for j in range(1, n+1):
        table[0][j] = j
    
    for i in range(1, m+1):
        for j in range(1, n+1):
            if (s1[i-1] == s2[j-1]):
                table[i][j] = table[i-1][j-1]
            else:
                table[i][j] = min(table[i-1][j-1], table[i-1][j], table[i][j-1]) + 1

    return table[m][n]

print(minDistance("intention","execution"))

