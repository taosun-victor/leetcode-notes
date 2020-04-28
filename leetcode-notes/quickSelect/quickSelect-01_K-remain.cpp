#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void partition(vector<pair<int, int>>& nums, int left, int right, int k, int target){
    if (left >= right)
        return;

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

    if (i == k)
        return;
    else if (i < k)
        partition(nums, i + 1, right, k, target);
    else
        partition(nums, left, i - 1, k, target);
}

vector<int> quickSelect(vector<pair<int, int>>& nums, int k, int target){
    partition(nums, 0, nums.size() - 1, k, target);
    vector<int> res;
    for (int i = 0; i < k; i++)
        res.push_back(nums[i].second);
    return res;
}

int main(){
    vector<int> vec{3, 6, 8, 1, 10, 30, 20, 16, 17, 25, 14};
    int target = 15, k = 11;
   
    vector<pair<int, int>> nums;
    for (int i = 0; i < vec.size(); i++)
        nums.push_back({vec[i], i});
       
    vector<int> res = quickSelect(nums, k, target);
   
    for (int& r : res)
        cout << r << " ";
    cout << endl;

    return 0;
}
