#include<iostream>
#include<vector>
#include <string>
#include <stdlib.h>

using namespace std;

void reverse(string& input, int left, int right){
    while(left < right)
      swap(input[left++], input[right--]);
}

void convert(string& array, int left, int right){
    if (right - left <= 1)
      	return;

    int len = right - left + 1;
    int mid = left + len / 2;
   	int leftMid = left + len / 4;
    int rightMid = left + len * 3 / 4;

   	reverse(array, leftMid, mid - 1);
   	reverse(array, mid, rightMid - 1);
   	reverse(array, leftMid, rightMid - 1);

   	convert(array, left, left + 2 * (leftMid - left) - 1);
    convert(array, left + 2 * (leftMid - left), right);
}

string reorder(string array) {
    if (array.empty()) return array;
    int right = (array.size() % 2 == 0 ? array.size() - 1 : array.size() - 2);
    convert(array, 0, right);
    return array;
}

int main() {
	cout << reorder("ABCDE12345") << endl;
	cout << reorder("ABCD1234") << endl;
	return 0;
}
