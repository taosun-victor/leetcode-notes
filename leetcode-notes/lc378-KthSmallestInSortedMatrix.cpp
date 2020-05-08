#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

//------------------------ sol 1---------------
// time O(n * log(MAX - MIN)), space O(1)

// check num of smaller elems than target, whether it is >= K
bool count(vector<vector<int>>& matrix, int target, int k){
    int n = matrix.size();
    int cnt = 0, i = n - 1, j = 0;
    while(i >= 0 && j < n){
        if (matrix[i][j] <= target){
            j++;
            cnt += (i + 1);
        }
        else 
            i--;
    }
    return cnt >= k;
}

int kthSmallest_sol1(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int left = matrix[0][0], right = matrix[n - 1][n - 1];
    while(left < right){
        int mid = left + (right - left) / 2;
        if (count(matrix, mid, k))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
// One more question here: how could you ensure that the returned value "left" exist in the input matrix? 



    
//------------------------ sol2 -----------------
// time O(k * log(k)), space O(k)

int kthSmallest_sol2(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
    unordered_set<int> set;
    
    q.push({matrix[0][0], 0, 0});
    set.insert(0 * n + 0);
    
    for (int i = 0; i < k - 1; i++){
        vector<int> curr = q.top();
        q.pop();
        
        int val = curr[0], row = curr[1], col = curr[2];
        if (row + 1 < n && !set.count((row + 1) * n + col)){
            q.push({matrix[row + 1][col], row + 1, col});
            set.insert((row + 1) * n + col);
        }
        if (col + 1 < n && !set.count(row * n + col + 1)){
            q.push({matrix[row][col + 1], row, col + 1});
            set.insert(row * n + col + 1);
        }
    }
    return q.top()[0];
}



//------------------ sol 3 -------------------------
// time O(k * log(n)), space O(k)

int kthSmallest_sol3(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;

    for (int i = 0; i < min(n, k); i++)
        q.push({matrix[i][0], i, 0});
    
    for (int i = 0; i < k - 1; i++){
        vector<int> curr = q.top();
        q.pop();
        
        int val = curr[0], row = curr[1], col = curr[2];
        if (col + 1 < n)
            q.push({matrix[row][col + 1], row, col + 1});
    }
    return q.top()[0];
}



//------------------ main function --------------------
int main() {
	vector<vector<int>> M{{1,  5,  9 },
                          {10, 11, 13},
                          {12, 13, 15}};
                          
    cout << kthSmallest_sol3(M, 8) << endl;
    return 0;
}
