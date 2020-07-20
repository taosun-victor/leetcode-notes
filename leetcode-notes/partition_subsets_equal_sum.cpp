#include<iostream>
#include<vector> 
#include<numeric>

using namespace std;

// count, in case of target group sum = 0, must take the current element to go through
bool dfs(vector<int>& nums, int idx, int k, int curSum, int target, int count, vector<int>& visit){
    if (k == 1)
        return true;
        
    if (curSum == target && count > 0)
        return dfs(nums, 0, k - 1, 0, target, 0, visit);
    
    for (int i = idx; i < nums.size(); i++){
        if (visit[i])
			continue;
			
        visit[i] = 1;
        if (dfs(nums, i + 1, k, curSum + nums[i], target, count, visit))
            return true;
        count++;
        visit[i] = 0;
    }
    return false;
}

bool canPartitionKSubsets(vector<int>& nums, int k) {
    if (nums.size() < k)
        return false;
    
    int totSum = accumulate(nums.begin(), nums.end(), 0);
    if (totSum % k != 0)
        return false;
    
    vector<int> visit(nums.size(), 0);
    return dfs(nums, 0, k, 0, totSum / k, 0, visit);
}

int main() {
	vector<int> input{-1,1,0,0};
	int k = 4;
	cout << canPartitionKSubsets(input, k) << endl;
}
