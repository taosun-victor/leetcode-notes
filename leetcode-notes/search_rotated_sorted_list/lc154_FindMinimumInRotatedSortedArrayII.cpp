#include <iostream>
#include <vector>

//************************************ sol1 ********************************
// the function is exactly the same with sol1 of lc153
int findMin1(vector<int>& nums) {
    return findKey(nums, 0, nums.size() - 1);
}

bool isSorted(vector<int>& nums, int start, int end){
    return nums[start] < nums[end];
}

int findKey(vector<int>& nums, int left, int right){
    if (left == right)
        return nums[left];
    if (left + 1 == right)
        return min(nums[left], nums[right]);
    
    int mid = left + (right - left) / 2;
    return min(findKey(nums, left, mid), findKey(nums, mid + 1, right));
}

//*********************************** sol2 ***********************************
int findMin2(vector<int>& nums) {
    if (nums.size() == 1)
        return nums[0];
    int left = 0, right = nums.size() - 1;

    //rotate at index 0: overall sorted  <-------------------------------------
    if (nums[left] < nums[right])                                         //  |
        return nums[left];                                                //  |
                                                                          //  | 
    while(left <= right){                                                 //  |
        int mid = left + (right - left) / 2;                              //  |
        if (nums[mid] > nums[mid + 1])                                    //  |
            return nums[mid + 1];                                         //  | 
	                                                                  //  |
	// it IS necessary to check mid - 1 >= 0 here                         |
	// in case of [1, 1, 1, 1]                                            |
	// which is not covered by preCheck -----------------------------------
        if (mid - 1 >= 0 && nums[mid - 1] > nums[mid]) 
            return nums[mid];
        
        if (nums[mid] < nums[right])
            right = mid - 1;
        else if (nums[mid] > nums[right])
            left = mid + 1;
	else
	    right--;
    }
    return nums[left];
}


//******************** main function ****************************************
int main() {
    vector<int> v{4,5,6,7,0,1,2};
    return findMin2(v);
}

// time complexity: O(N)
