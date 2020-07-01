#include <iostream>
#include <vector>

using namespace std;

class countArray {
private:
    class Item {
    public:
        int val;
        int idx;
        
        Item(int val, int idx){
            this->val = val;
            this->idx = idx;
        }
    };
    
public:
    vector<int> countSmaller(const vector<int>& nums) {
        int n = nums.size();
        vector<Item*> items;
        for (int i = 0; i < n; i++){
            items.push_back(new Item(nums[i], i));
        }
        
        vector<int> counts(n, 0);
        vector<Item*> helper(n, NULL);
        mergeSort(items, 0, n - 1, helper, counts);
        
        for (int i = 0; i < n; i++)
        	delete items[i];
        
        return counts;
    }
    
    void mergeSort(vector<Item*>& items, int left, int right, vector<Item*>& helper, vector<int>& counts){
        if (left >= right)
            return;
        int mid = left + (right - left) / 2;
        mergeSort(items, left, mid, helper, counts);
        mergeSort(items, mid + 1, right, helper, counts);
        merge(items, left, right, mid, helper, counts);
    }
    
    void merge(vector<Item*>& items, int left, int right, int mid, vector<Item*>& helper, vector<int>& counts){
        for (int i = left; i <= right; i++)
            helper[i] = items[i];
        
        int rightSmaller = 0;
        int i = left, j = mid + 1, k = left;
        while(i <= mid && j <= right){
            if (helper[i]->val > items[j]->val){
                rightSmaller++; // left one > right one, 
                items[k++] = items[j++];
            }
            else{
                counts[helper[i]->idx] += rightSmaller;
                items[k++] = helper[i++];
            }
        }
        while(i <= mid){
            counts[helper[i]->idx] += rightSmaller;
            items[k++] = helper[i++];
        }
    }
};
/*
            (5,0) (2,1) (6,2) (1,3)
        (5,0) (2,1)          (6,2) (1,3)
      (5,0)      (2,1)    (6,2)       (1,3)
  -----------------------------------------------
       (2,1,0)(5,0,1)        (1,3,0)(6,2,1)
                i                      j
          (1,3,0)(2,1,1)(5,0,2)(6,2,1)
          
                --> [2, 1, 1, 0]
*/

int main() {
	vector<int> input{5, 2, 6, 1};
	countArray* countA = new countArray();
	vector<int> countRightSmaller = countA->countSmaller(input);
	for (int i : countRightSmaller)
		cout << i << " ";
	cout << endl;
}

