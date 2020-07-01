#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void shuffle(vector<pair<int, int>>& dirs){
	for (int i = 0; i < 4; i++){
  		int r = i + rand() % (4 - i);
  		swap(dirs[i], dirs[r]);
	}
}

void genRandomMaze(vector<vector<int>>& grids, int row, int col){
	int m = grids.size(), n = grids[0].size();
	vector<pair<int, int>> currDirs = dirs;
	shuffle(dirs);
	
	for (auto dir : currDirs){
  		int mid_row = row + dir.first, mid_col = col + dir.second;
  		int next_row = row + 2 * dir.first, next_col = col + 2 * dir.second;
  		if (next_row >= 0 && next_row < m && next_col >= 0 && next_col < n && grids[next_row][next_col] == 1){
    		grids[mid_row][mid_col] = 0;
    		grids[next_row][next_col] = 0;
    		genRandomMaze(grids, next_row, next_col);
  		}
	}
}

vector<vector<int>> getMaze(int m, int n) {	
	vector<vector<int>> grids(m, vector<int>(n, 1));
	grids[0][0] = 0;
	
	genRandomMaze(grids, 0, 0);
	return grids;
}

int main() {
	vector<vector<int>> myMaze;
	for (int k = 0; k < 10; k++){
		
		myMaze = getMaze(53, 51);
		for (auto m : myMaze){
			for (int i : m)
				cout << i << " ";
			cout << endl;
		}
		cout << "-----------------------" <<endl;
	}
	return 0;
}
