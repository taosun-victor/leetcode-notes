#include <iostream>
#include <vector>

//********************************* solution ********************
bool search(vector<int>& nums, int target) {
    if (nums.empty()) return false;
    int left = 0, right = nums.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return true;
        if (nums[mid] < nums[right]){
            if (nums[mid] < target && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
        else if (nums[mid] > nums[right]){
            if (nums[left] <= target && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
        else
            right--;
    }
    return false;
}


//*********************************** main function ***************************
int main() {
    vector<int> v{2,5,6,0,0,1,2};
    int target = 0;
    int idx = search(v, target);
    cout << idx << endl;
    return 0;
}

// time complexity: O(N)
