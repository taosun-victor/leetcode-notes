#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void keepDist1(int k, int idx, vector<int>& out, vector<vector<int>>& res, unordered_map<int, int>& pos){
	if (idx == 2 * k){
		res.push_back(out);
		return;
	}
	
	for (int i = 1; i <= k; i++){
		out.push_back(i);
		bool flag = false;
		if (!pos.count(i) || idx - pos[i] == i + 1){
			if (!pos.count(i)){			
				flag = true;
				pos[i] = idx;
			}
			keepDist1(k, idx + 1, out, res, pos);
			if (flag)
				pos.erase(i);
		}	
		out.pop_back();
	}
}

void keepDist2(int k, int idx, vector<int>& out, vector<vector<int>>& res){
	if (idx == k + 1){
		res.push_back(out);
		return;
	}
	
	for (int i = 0; i < out.size(); i++){
		if (out[i] == 0 && i + idx + 1 < out.size() && out[i + idx + 1] == 0){
			out[i] = idx;
			out[i + idx + 1] = idx;
			keepDist2(k, idx + 1, out, res);
			out[i] = 0;
			out[i + idx + 1] = 0;
		}
	}
}

int main() {
	unordered_map<int, int> pos;
	vector<int> out;
	vector<vector<int>> res;
	int k = 7;
	
	//keepDist1(8, 0, out, res, pos);
	
	out.resize(2 * k, 0);
	keepDist2(k, 1, out, res);
	
	for (auto v : res){
		for (int i : v)
			cout << i << " ";
		cout << endl;
	}
	
	return 0;
}
