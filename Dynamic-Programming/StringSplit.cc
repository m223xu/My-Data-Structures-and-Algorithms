/*
Another version of Matrix Chain Multiplication problem.

Given string S with length n and a vector L with
length m that records m spots at which we want to split.
1 <= L[i] < L[j] <= n-1 for all 1 <= i < j <= m.
A split of string of length n costs n units of time.
Our goal is to calculate the minimum cost (and the order to split).
*/


#include <vector>
#include <iostream>

using namespace std;

int split(int n, vector<int> L)
{
	int m = L.size();
	vector<vector<int>> cost;
  
	L.insert(L.begin(), 0);
	L.emplace_back(n);
	
  for (int i = 0; i <= m + 1; ++i)
	{
		vector<int> row(m + 2, INT_MAX);
		cost.emplace_back(row);
	}
	for (int i = 0; i <= m; ++i) cost[i][i + 1] = 0;

	for (int l = 2; l <= m + 1; ++l)
	{
		for (int i = 0; i <= m - l + 1; ++i)
		{
			int j = i + l;
			int addition = L[j] - L[i];
			for (int k = i + 1; k <= j - 1; ++k)
			{
				int c = addition + cost[i][k] + cost[k][j];
				if (c < cost[i][j])
				{
					cost[i][j] = c;
				}
			}
		}
	}
	return cost[0][m + 1];
}
