#include <iostream>
#include <vector>

//******************** sol1 ********************
int search1(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < nums[right]){
            if (nums[mid] < target && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
        else{
            if (nums[mid] > target && target >= nums[left])
                right = mid - 1;
            else 
                left = mid + 1;
        }
    }
    return -1;
}

//******************** sol2 ********************
int search2(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] >= nums[left]) {// notice here it is >=, in case [3, 1]
            if (nums[mid] > target && target >= nums[left])
                right = mid - 1;
            else 
                left = mid + 1;
        }
	else{
            if (nums[mid] < target && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
}

//************************** main function *****************
int main() {
    vector<int> v{4, 5, 6, 7, 0, 1, 2};
    int idx = search1(v, 6);
    cout << idx << endl;
    return 0;
}

// time complexity: O(logN)
