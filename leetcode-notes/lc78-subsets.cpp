#include <vector>
#include <iostream>

using namespace::std;

/***************************************** sol1 *******************************************/
void dfs1(vector<int>& nums, vector<int>& out, int idx, vector<vector<int>>& res){
    if (idx == nums.size()){
        res.push_back(out);
        return;
    }
    
    out.push_back(nums[idx]);
    dfs(nums, out, idx + 1, res);
    out.pop_back();
    
    dfs(nums, out, idx + 1, res);
}

vector<vector<int>> subsets1(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> out;
    dfs1(nums, out, 0, res);
    return res;
}

/*************************************** sol2 ******************************************/
void dfs2(vector<int>& nums, vector<int>& out, int idx, int k, vector<vector<int>>& res){
    if (out.size() == k){
        res.push_back(out);
        return;
    }

    for (int i = idx; i < nums.size(); i++){
        out.push_back(nums[i]);
        dfs(nums, out, i + 1, k, res);
        out.pop_back();
    }
}

vector<vector<int>> subsets2(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> out;
    for (int k = 0; k <= nums.size(); k++)
        dfs2(nums, out, 0, k, res);
    return res;
}

//*********************************** all permutations of subsets ***********************************
vector<string> allPermutationsOfSubsets(string set) {
    // write your solution here
    int n = set.size();
    string out;
    unordered_set<char> visit;
    vector<string> res;
    for (int k = 0; k <= n; k++)
        dfs_all_permutations_of_subsets(set, out, k, visit, res);
    return res;
}
    
void dfs_all_permutations_of_subsets(string& set, string& out, int k, unordered_set<char>& visit, vector<string>& res){  
    if (out.size() == k){
        res.push_back(out);
        return;
    }
    
    for (int i = 0; i < set.size(); i++){
        if (visit.count(set[i]))
            continue;
        visit.insert(set[i]);
        out.push_back(set[i]);
        dfs(set, out, k, visit, res);
        out.pop_back();
        visit.erase(set[i]);
    }
} 

//*************************************************************************************************
/*************************************** sol3 ****************************************************/
void dfs3(vector<int>& nums, int idx, vector<vector<int>>& res){
    if (idx == nums.size()){
        res.push_back({});
        return;
    }

    dfs(nums, idx + 1, res);

    int size = res.size();
    for (int i = 0; i < size; i++){
        vector<int> v = res[i];
        v.push_back(nums[idx]);
        //v.push_back(nums[nums.size() - 1 -idx]);
	res.push_back(v);
    }
}

vector<vector<int>> subsets3(vector<int>& nums) {
    vector<vector<int>> res;
    dfs(nums, 0, res);
    return res;
}

/*************************************** sol4 **************************************************/
void dfs4(vector<int>& nums, vector<int>& out, int idx, vector<vector<int>>& res){
    res.push_back(out);
    for (int i = idx; i < nums.size(); i++){
        out.push_back(nums[i]);
        dfs(nums, out, i + 1, res);
        out.pop_back();
    }
}

vector<vector<int>> subsets4(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> out;
    dfs(nums, out, 0, res);
    return res;
}

/*===================================== Main Function ==================================================*/
int main() {
    vector<int> nums{1, 2, 3};

    vector<vector<int>> res = subsets(nums);
    for (auto r : res){
        for (int i : r)
	    cout << i << " ";
	cout << endl;
    }
    return 0;
}
