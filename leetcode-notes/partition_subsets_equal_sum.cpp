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


//================================================================================
bool checkSum(vector<int>& sumLeft){
    for (int s : sumLeft){
        if (s != 0)
            return false;
    }
    return true;
} 

bool helper(vector<int>& nums, int idx, vector<int>& sumLeft, vector<int>& pos, int k){
    if (checkSum(sumLeft))
        return true;
    
    if (idx < 0)
        return false;
    
    bool res = false;
    for (int i = 0; i < k; i++){
        if (!res && sumLeft[i] - nums[idx] >= 0){
            pos[idx] = i + 1;
            sumLeft[i] -= nums[idx];
            res = helper(nums, idx - 1, sumLeft, pos, k);
            sumLeft[i] += nums[idx];
        }
    }
    return res;
}

bool canPartitionKSubsets_Sol2(vector<int>& nums, int k) {
    int n = nums.size();
    if (n < k)
        return false;
    
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % k != 0)
        return false;
    
    vector<int> pos(n), sumLeft(k);
    for (int i = 0; i < k; i++)
        sumLeft[i] = sum / k;
    
    bool res = helper(nums, n - 1, sumLeft, pos, k);
    if (res){
        for (int i = 0; i < k; i++){
            cout << "Pattern " << i << ": ";
            for (int j = 0; j < n; j++){
                if (pos[j] == i + 1)
                    cout << nums[j] << " ";
            }
            cout << endl;
        }
    }
    return res;
}


int main() {
	//vector<int> input{4, 3, 2, 3, 5, 2, 1};
	vector<int> input{-1,1,0,0};
	int k = 4;
	cout << canPartitionKSubsets_Sol2(input, k) << endl;
}
