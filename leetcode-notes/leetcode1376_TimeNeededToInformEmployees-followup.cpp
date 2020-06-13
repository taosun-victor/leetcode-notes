#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

vector<int> bfs(vector<vector<int>>& graph, vector<int>& informTime, int headID){
    vector<int> res;
    auto cmp = [](pair<int, int>& p1, pair<int, int>& p2){
    	return p1.second > p2.second || (p1.second == p2.second && p1.first > p2.first);
	};
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
    q.push({headID, informTime[headID]});
    
    while(!q.empty()){
        int size = q.size();
            pair<int, int> curr = q.top();
            q.pop();
            
            int currEmployee = curr.first, currTimeCost = curr.second;
            res.push_back(currEmployee);
            
            for (int sub : graph[currEmployee])
                q.push({sub, currTimeCost + informTime[sub]});
    }
    return res;
}

vector<int> numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; i++){
        if (manager[i] != -1)
            graph[manager[i]].push_back(i);
    }
            
    return bfs(graph, informTime, headID);
}
    
/*

We would like to print the order of Employees with their time of finishing reading the msg

                            4 (1)(1)
                            |
                            10 (2)(3)
                            | 
                            3 (3)(6)
                            |
                            9 (5)(11)
                       /      |           \ 
                    1(30)(41) 6(10)(21)   8(15)(26)
                     |        |             |
                    7(10)(51) 2(23)(41)   5(5)(36)
                                           |
                                          0(1)(37)

--> order of finish: 4, 10, 3, 9, 6, 8, 5, 0, 1, 2, 7 


Followup 2: What about if one employee could report to more than one managers?
*/


int main() {
	int n = 11;
    int headID = 4;
    vector<int> managers{5,9,6,10,-1,8,9,1,9,3,4};
    vector<int> informTime{1,30,23,3,1,5,10,10,15,5,2};
    
    vector<int> res = numOfMinutes(n, headID, managers, informTime);
    
    for (int i : res)
    	cout << i << " ";
    cout << endl;
    
    return 0;
    
}
