#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void partition(vector<pair<int, int>>& nums, int left, int right, int k, int target, vector<int>& res){
    if (k == 0) return;
    int pivot = abs(nums[right].first - target);
    int i = left, j = left;
    while(j < right){
        if (abs(nums[j].first - target) < pivot){
            swap(nums[i], nums[j]);
            i++;
        }
        j++;
    }
    swap(nums[i], nums[right]);
   
    if (i - left + 1 <= k){
        for (int p = left; p <= i; p++)
            res.push_back(nums[p].second);
        partition(nums, i + 1, right, k - i + left - 1, target, res);
    }
    else{
        partition(nums, left, i - 1, k, target, res);
    }
}

int main(){
    vector<int> vec{3, 6, 8, 1, 10, 30, 20, 16, 17, 25, 14};
    int target = 15, k = 11;
   
    vector<pair<int, int>> nums;
    for (int i = 0; i < vec.size(); i++)
        nums.push_back({vec[i], i});
       
    vector<int> res;
    partition(nums, 0, nums.size() - 1, k, target, res);
   
    for (int& r : res)
        cout << r << " ";
    cout << endl;

    return 0;
}
