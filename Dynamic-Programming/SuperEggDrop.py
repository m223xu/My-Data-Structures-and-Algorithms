'''
You are given K eggs, and you have access to a building with N floors from 1 to N. 
Each egg is identical in function, and if an egg breaks, you cannot drop it again.
You know that there exists a floor F with 0 <= F <= N such that any egg dropped at a floor higher than F will break,
and any egg dropped at or below floor F will not break.
Each move, you may take an egg (if you have an unbroken one) and drop it from any floor X (with 1 <= X <= N). 
Your goal is to know with certainty what the value of F is.
What is the minimum number of moves that you need to know with certainty what F is, regardless of the initial value of F?
'''

'''
dp(K,N) = min (1+max(dp(K−1,X−1),dp(K,N−X)))
'''

'''
A general approach will take O(K*N^2) since we will 
use O(N) time to solve each of the O(KN) subproblems.
'''

'''
However, we can make improvement.
dp(K-1,X-1) is increasing, dp(K,N-X) is decreasing.
If we already know the optimal value of X for problem
of size (K,n) is X_n, then the optimal value of X 
for problem of size (K, n+1) is actually greater than X_n.
(
This is because the optimal value of X for problem of size (K,n)
tries to make dp(K-1,X-1) and dp(K,n-X) equal.
And when the problem size increase, the second term is larger.
Decreasing X = X_n will make it even larger so the difference
cannot be minimized. Therefore, we will increase X to X_(n+1).
)
So we will record X_n for solving the next subproblem.
'''



def superEggDrop(K, N):

        # Right now, dp[i] represents dp(1, i)
        dp = range(N+1)

        for k in range(2, K+1):
            # Now, we will develop dp2[i] = dp(k, i)
            dp2 = [0]
            x = 1
            for n in range(1, N+1):
                # Let's find dp2[n] = dp(k, n)
                # Increase our optimal x while we can make our answer better.
                # Notice max(dp[x-1], dp2[n-x]) > max(dp[x], dp2[n-x-1])
                # is simply max(T1(x-1), T2(x-1)) > max(T1(x), T2(x)).
                while x < n and max(dp[x-1], dp2[n-x]) > \
                                max(dp[x], dp2[n-x-1]):
                    x += 1

                # The final answer happens at this x.
                dp2.append(1 + max(dp[x-1], dp2[n-x]))

            dp = dp2

        return dp[-1]

print(superEggDrop(2,200))
print(superEggDrop(3,14))
print(superEggDrop(2,6))


#Leetcode 887

