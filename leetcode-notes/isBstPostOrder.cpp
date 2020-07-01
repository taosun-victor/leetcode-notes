#include <iostream>
#include <vector>

using namespace std;

// vec: [2, 4, 3, 6, 9, 8, 5]
/*
         5
        / \
      3    8
     / \   /\
	2  4  6  9 
	
	5
	 \
	  8
	   \
	    9
	    \
		 10
		  \
		  12
	
	
*/

bool isPostBST(const vector<int>& vec, int pStart, int pEnd, int minVal, int maxVal){
	if (pStart > pEnd)
		return true;
	
	if (vec[pEnd] <= minVal || vec[pStart] >= maxVal)
		return false;
		
	int idx = pEnd;
	while(idx >= pStart){
		if (vec[idx] < vec[pEnd])
			break;
		idx--;
	}
	
	return isPostBST(vec, pStart, idx, minVal, vec[pEnd]) &&
	       isPostBST(vec, idx + 1, pEnd - 1, vec[pEnd], maxVal);
}

bool isPost(const vector<int>& vec){
	return isPostBST(vec, 0, vec.size() - 1, INT_MIN, INT_MAX);
}

int main() {
	//vector<int> vec{2,4,3,6,9,8,5};
	//vector<int> vec{4,2,3,6,9,8,5};
	vector<int> vec{12,10,8,9,5};
	cout << isPost(vec) << endl;
	return 0;
}
