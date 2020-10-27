#include <vector>
#include <iostream>

using namespace std;

int knapsack(vector<int>& weight, vector<int>& value, int W){
	/* dp[i][j] represents the max total value when dealing first i items with total weight <= j

	   base case:
	   dp[0][0] = 0
	   
	   induction rule:
	   case 1: take current item
	   M[i - 1][j - weight[i - 1]] + value[i - 1], if j >= weight[i - 1]
	   
	   case 2: no take current item
	   M[i - 1][j]
	   
	   take the max
	   
	   finally return M[n][W]
	*/
	
	int n = value.size();
	vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= W; j++){
			int takeCurr = 0;
			if (j >= weight[i - 1])
				takeCurr = dp[i - 1][j - weight[i - 1]] + value[i - 1];
			
			int noTakeCurr = dp[i - 1][j];
			
			dp[i][j] = max(takeCurr, noTakeCurr);								
		}
	}
	return dp[n][W];
} 


int main() {
	vector<int> val{10, 40, 30, 50};
	vector<int> wt{5, 4, 6, 3};
	
	cout << knapsack(wt, val, 10) << endl;
}
