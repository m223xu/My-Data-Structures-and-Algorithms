'''
Given a string and an integer m, each time we can swap two adjacent characters.
We want to find that within at most m steps, at most how many same consecutive letters
are there in s.
'''

'''
For each character, v is the list recording indices of this character in s. 

dp[left][right] is the number of steps to make all these (right-left+1) characters
(of the same type) in a row.

To evaluate dp[left][right], we require dp[left+1][right-1] for a subset of these
characters to be in a row at first, and the outer 2 characters to concatenate.

dp[left][right] = dp[left+1][right-1] + (v[right]-v[left]-1) - (right-left-1)
'''

s, m = input().split()
m = int(m)
 
from collections import defaultdict
 
d = defaultdict(list) # the map from characters to lists of positions
 
for i,c in enumerate(s):
    d[c].append(i)
 
res = 0
for k,v in d.items():
    n = len(v)
    dp = [[0] * n for _ in range(n)]
    for k in range(1,n):
        for i in range(n-k):
            left, right = i, k+i
            dp[left][right] = dp[left+1][right-1] + (v[right] - v[left] - 1) - (right - left - 1)
 
    for i in range(n):
        for j in range(i,n):
            if dp[i][j] <= m:
                res = max(res, j-i+1)
 
print(res)