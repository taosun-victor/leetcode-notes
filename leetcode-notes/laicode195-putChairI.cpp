#include <iostream>
#include <vector> 
#include <queue>

using namespace std;

 void printM(vector<vector<int>>& m){
 	for (int i = 0; i < m.size(); i++){
 		for (int j = 0; j < m[0].size(); j++)
		 	cout << m[i][j] << " ";
		cout << endl;	
	}
	cout << endl;
 }
 
  vector<int> putChair(const vector<vector<char>>& gym) {
    // write your solution here
    if (gym.empty() || gym[0].empty())
      return {-1, -1};
    int m = gym.size(), n = gym[0].size();
    int equipCount = 0;
    vector<vector<int>> counts(m, vector<int>(n, 0));
    vector<vector<int>> dists(m, vector<int>(n, 0));
    vector<vector<int>> dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (int i = 0; i < m; i++){
      for (int j = 0; j < n; j++){
        if (gym[i][j] != 'E')
          continue;

		
        equipCount++;
        int steps = 0;
        queue<vector<int>> q;
        vector<vector<int>> visit(m, vector<int>(n, 0));
        q.push({i, j});
        visit[i][j] = 1;

        while(!q.empty()){
          steps++;
          int size = q.size();
          for (int k = 0; k < size; k++){
            vector<int> curr = q.front(); 
            q.pop();

            for (auto dir : dirs){
              int row = curr[0] + dir[0], col = curr[1] + dir[1];
              if (row < 0 || row >= m || col < 0 || col >= n || gym[row][col] == 'O' || visit[row][col] )
                continue;
              
              visit[row][col] = 1;
              counts[row][col]++;
              dists[row][col] += steps;
              //if (counts[row][col] == equipCount)
                q.push({row, col});
            }
          }
        }
        
        cout << "equip counts: " << equipCount << endl;
        printM(counts);
        cout << "-------------------------" << endl;
      }
    }

	//cout << "equip counts: " << equipCount << endl;

	//cout << "counts: " << endl;
	//printM(counts);
	//cout << "dists: " << endl;
	//printM(dists);
	
    vector<int> pos{-1, -1};
    int minDist = INT_MAX;
    for (int i = 0; i < m; i++){
      for (int j = 0; j < n; j++){
        if (gym[i][j] == 'C' && counts[i][j] == equipCount){
          if (dists[i][j] < minDist){
            minDist = dists[i][j];
            pos = {i, j};
          }
        }
      }
    }
    return pos;
  }
  
  
int main(){
	vector<vector<char>> gym{{'E','C','E','O','C'},
							 {'E','O','C','C','E'},
							 {'O','O','E','C','C'},
							 {'C','O','C','E','E'},
							 {'E','C','C','C','C'}};
					 
	vector<int> pos = putChair(gym);
	cout << pos[0] << " " << pos[1] << endl;
}
