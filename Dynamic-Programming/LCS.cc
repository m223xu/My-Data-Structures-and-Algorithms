// lcs returns the longest common subsequence of two strings

// e.g. lcs("acd", "bcde") = "cd"

#include <vector>

using namespace std;

string lcs(string x, string y)
{
	int m = x.length();
	int n = y.length();
	vector<vector<string>> table;
	for (int i = 0; i <= m; ++i)
	{
		vector<string> row(n + 1, "");
		table.emplace_back(row);
	}
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (x[i - 1] == y[j - 1])
			{
				table[i][j] = table[i - 1][j - 1] + x[i - 1];
			}
			else if (table[i - 1][j].length() >= table[i][j - 1].length())
			{
				table[i][j] = table[i - 1][j];
			}
			else
			{
				table[i][j] = table[i][j - 1];
			}
		}
	}
	return table[m][n];
}
