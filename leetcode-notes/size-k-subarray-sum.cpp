#include <iostream>
#include <vector>

using namespace std;

int maxSumSubarray(const vector<int>& input, int k){
	int sum = 0, res = 0;
	for (int i = 0; i < input.size(); i++){
		if (i < k){
			sum += input[i];
			if (i == k - 1)
				res = sum;
		}
		else{
			sum += (input[i] - input[i - k]);
			res = max(res, sum);
		}
	}
	return res;
}

int maxSumTwoNonOverlapSubarray(const vector<int>& input, int k){
	if (input.size() < 2 * k)
		return -1;
		
	int n = input.size(), maxWindow = INT_MIN;
	vector<int> window(n, INT_MIN); // window[i] represents the max sum of the subarray ending before or at i
	
	int sum = 0, res = INT_MIN;
	for (int i = 0; i < n; i++){
		if (i < k){
			sum += input[i];
			if (i == k - 1){
				maxWindow = sum;
				window[i] = sum;
			}
		}
		else{	
			sum += (input[i] - input[i - k]);
			maxWindow = max(maxWindow, sum);
			window[i] = maxWindow;
		}
		if (i >= 2 * k - 1)
			res = max(res, sum + window[i - k]);
	}	
	return res;
}


int maxSumThreeNonOverlapSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    if (n < 3*k)
        return -1;
    
    vector<int> slideSum(n - k + 1, INT_MIN);
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += nums[i];
        if (i >= k)
            sum -= nums[i - k];
        
        if (i >= k - 1)
            slideSum[i - k + 1] = sum;
    }
    
    vector<int> left(n - k + 1, -1);
    vector<int> right(n - k + 1, -1);
    
    int maxVal = INT_MIN, maxIdx = -1;
    for (int i = 0; i < n - k + 1; i++){
        if (slideSum[i] > maxVal){
            maxVal = slideSum[i];
            maxIdx = i;
        }
        left[i] = maxIdx;
    }
    
    maxVal = INT_MIN, maxIdx = n - k + 1;
    for (int i = n - k; i >= 0; i--){
        if (slideSum[i] >= maxVal){
            maxVal = slideSum[i];
            maxIdx = i;
        }
        right[i] = maxIdx;
    }
    
    int res = INT_MIN;
    for (int i = k; i < n - 2* k + 1; i++){
        int currVal = slideSum[left[i - k]] + slideSum[i] + slideSum[right[i + k]];
        res = max(res, currVal);
    }
    return res;
}

void printList(const vector<int>& v){
	for (int i : v)
		cout << i << " ";
	cout << endl;
}

int dfs(vector<int>& slideSum, int idx, int m, int k){
    if (m == 0)
        return 0;
    
    if (idx >= slideSum.size()){
    	return (m > 0 ? INT_MIN : 0);
	}
    
    int val1 = slideSum[idx] + dfs(slideSum, idx + k, m - 1, k);
    int val2 = dfs(slideSum, idx + 1, m, k);
    
    return max(val1, val2);
}


int maxSumMNonOverlapSubarray(vector<int>& nums, int k, int m) {
    int n = nums.size();
    if (n < m * k)
        return -1;
    
    vector<int> slideSum(n - k + 1, INT_MIN);
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += nums[i];
        if (i >= k)
            sum -= nums[i - k];
        
        if (i >= k - 1)
            slideSum[i - k + 1] = sum;
    }

	printList(nums);
	printList(slideSum);

	cout <<  dfs(slideSum, 0, m, k) << endl;
    
	vector<vector<int>> dp(n - k + 1, vector<int>(m + 1, 0));
    
    for (int i = 0; i < n - k + 1; i++){
        for (int j = 1; j <= m; j++){
        		int val1 = (i - 1 >= 0 ? dp[i - 1][j] : 0);
        		int val2 = (i - k >= 0 ? dp[i - k][j - 1] : 0 ) + slideSum[i];
                dp[i][j] = max(val1, val2);
        }    
    }
    return dp[n - k][m];
}




int main(){
	vector<int> arr{2, 5, 1, 2, 7, 3, 0, 1, 4, 2, 5, 2, 3};
	//cout << "2 subarrays: " << maxSumTwoNonOverlapSubarray(arr, 2) << endl;
	cout << "m subarrays (m = 2): " << maxSumMNonOverlapSubarray(arr, 2, 4) << endl;
} 
