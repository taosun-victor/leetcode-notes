#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/*e.g. [1, 2, 0, 3, 0, 3, 2, 1], k = 4
 [1, 2, | 0, 3,| 0, 3,| 2, 1], [1, 2, | 0, 3, 0,| 3,| 2, 1], 
 [1, 2, 0,| 3,| 0, 3,| 2, 1], [1, 2, 0,| 3, 0,| 3,| 2, 1], 

prefixSum [1, 3, 3, 6, 6, 9, 11, 12] 
--> find in prefixSum how many subsequences of {3,6,9}

groupSum = totalSum / k
in general need to find in prefixSum the number of subsequences of {groupSum, 2 * groupSum, ... (k - 1) * groupSum}

M[i][j] represents the number of subsequences of {groupSum, 2 * groupSum, ... j * groupSum} within prefixSum
0-th to i-th element, that must include i-th element

base case:
	M[i][0] = 1
	M[0][j] = (input[0] == j * groupSum), j = 1, 2, .. k - 1

induction rule:
case 1: prefixSum[i] = j * groupSum
        M[i][j] = M[i - 1][j - 1] + M[i - 1][j]
        
case 2: prefixSum[i] != j * groupSum
		M[i][j] = M[i - 1][j]

*/
int numOfSplitSubarrayWithEqualSum(vector<int>& input, int k){
	if (k <= 0 || input.size() < k)
		return 0;
		
	int n = input.size();
	vector<int> prefixSum(n, 0);
	for (int i = 0; i < n; i++)
		prefixSum[i] = (i == 0 ? input[i] : input[i] + prefixSum[i - 1]);
		
	if (prefixSum[n - 1] % k != 0)
		return 0;
		
	int groupSum = prefixSum[n - 1] / k;	
	vector<vector<int>> dp(n, vector<int>(k, 0));
	
	for (int i = 0; i < n; i++)
		dp[i][0] = 1;
		
	for (int j = 1; j < k; j++)
		dp[0][j] = (prefixSum[0] == j * groupSum);
	
	for (int i = 1; i < n; i++){
		for (int j = 1; j < k; j++){
			if (prefixSum[i] == j * groupSum)
				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
			else
				dp[i][j] = dp[i - 1][j];
		}
	}
	
	return dp[n - 1][k - 1];
} 


int numOfSplitSubarrayWithEqualSum_Space(vector<int>& input, int k){
	if (k <= 0 || input.size() < k)
		return 0;
		
	int n = input.size();
	vector<int> prefixSum(n, 0);
	for (int i = 0; i < n; i++)
		prefixSum[i] = (i == 0 ? input[i] : input[i] + prefixSum[i - 1]);
		
	if (prefixSum[n - 1] % k != 0)
		return 0;
		
	int groupSum = prefixSum[n - 1] / k;	
	vector<vector<int>> dp(2, vector<int>(k, 0));
	
	dp[0][0] = 1;
	dp[1][0] = 1;
		
	for (int j = 1; j < k; j++)
		dp[0][j] = (prefixSum[0] == j * groupSum);
	
	for (int i = 1; i < n; i++){
		for (int j = 1; j < k; j++){
			if (prefixSum[i] == j * groupSum)
				dp[1][j] = dp[0][j - 1] + dp[0][j];
			else
				dp[1][j] = dp[0][j];
		}
		dp[0].swap(dp[1]);
	}
	
	return dp[0][k - 1];
} 

/*
further optimization:
if prefix[i] % groupSum == 0, directly update according to case 1 in the induction rule 

*/
int numOfSplitSubarrayWithEqualSum_Sol2(vector<int>& input, int k){
	if (k <= 0 || input.size() < k)
		return 0;
		
	int n = input.size();
	int sum = accumulate(input.begin(), input.end(), 0);
	if (sum % k != 0)
		return 0;
		
	int groupSum = sum / k;
	int prefixSum = 0;	
	vector<int> dp(k, 0);
	dp[0] = 1;
	
	for (int i = 0; i < n - 1; i++){
		prefixSum += input[i];
		if (prefixSum % groupSum == 0){
			int j = prefixSum / groupSum;
			dp[j] += dp[j - 1];
		}
	}
	
	return dp[k - 1];
} 

int main() {
	vector<int> input{1, 2, 0, 3, 0, 3, 2, 1};
	int k = 4;
	cout << numOfSplitSubarrayWithEqualSum_Sol2(input, k) << endl;
}
