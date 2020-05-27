#include <iostream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<int>>& matrix){
	for (int i = 0; i < matrix.size(); i++){
		for (int j = 0; j < matrix[0].size(); j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

int largestSquareOfMatches(vector<vector<int>> matrix) {
    // write your solution here
    if (matrix.empty() || matrix[0].empty())
      	return 0;

    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> M1(m, vector<int>(n, 0)); // right -> left
    vector<vector<int>> M2(m, vector<int>(n, 0)); // bottom -> up

    for (int i = 0; i < m; i++){
      	int count = 0;
      	for (int j = n - 1; j >= 0; j--){
        	count = (matrix[i][j] == 1 || matrix[i][j] == 3 ? count + 1 : 0);
        	M1[i][j] = count;
      	}
    }
    for (int j = 0; j < n; j++){
      	int count = 0;
      	for (int i = m - 1; i >= 0; i--){
        	count = (matrix[i][j] == 2 || matrix[i][j] == 3 ? count + 1 : 0);
        	M2[i][j] = count;
      	}
    }

	printMatrix(M1);
	printMatrix(M2);

    int res = 0;
    for (int i = 0; i < m; i++){
      	for (int j = 0; j < n; j++){
        	int len = min(M1[i][j], M2[i][j]);
        	for (int k = len; k >= 1; k--){
          		if (i + k < m && M1[i + k][j] >= k && 
				  	j + k < n && M2[i][j + k] >= k){
              		res = max(res, k);
              		break;
          		}
        	}
      	}
    }
    return res;
}
  
int main() {
	vector<vector<int>> input{{3, 1, 1, 3, 0, 1, 1, 0},
							  {2, 0, 0, 2, 0, 0, 0, 0},
 							  {3, 1, 3, 0, 0, 0, 0, 0},
							  {2, 0, 2, 0, 0, 0, 0, 0},
 							  {1, 1, 0, 0, 0, 0, 0, 0}};
 							  
 	int res = largestSquareOfMatches(input);
	cout << res << endl;
	
	return 0;
}
  
