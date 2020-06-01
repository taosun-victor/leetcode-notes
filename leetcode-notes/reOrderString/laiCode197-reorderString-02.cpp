#include<iostream>
#include<vector>
#include <string>
#include <stdlib.h>

using namespace std;

string merge(string s1, string s2){
	string res = "";
	int i = 0, j = 0;
	while(i < s1.size() && j < s2.size()){
		if (s1[i] < s2[j])
			res.push_back(s1[i++]);
		else
			res.push_back(s2[j++]);
	}
	while(i < s1.size())
		res.push_back(s1[i++]);
	while(j < s2.size())
		res.push_back(s2[j++]);
	//cout << res << endl;
	return res;
}

string mergeSort(string array, int left, int right){
	if (left == right){
		return string(1, array[left]);
	}
	
	int mid = left + (right - left) / 2;	
	
	return merge(mergeSort(array, left, mid), mergeSort(array, mid + 1, right));
}

string reorder(string s){
	return mergeSort(s, 0, s.size() - 1);
}

int main() {
	cout << reorder("A1B2C3D4") << endl;           // correct
	cout << reorder("A1B2C3D4E5") << endl;         // not correct
	cout << reorder("A1B2C3D4E5F6") << endl;       // not correct
	cout << reorder("A1B2C3D4E5F6G7H8") << endl;   // correct
	return 0;
}
