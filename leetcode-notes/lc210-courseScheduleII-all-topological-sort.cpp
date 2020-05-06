/***********************************************************************************

Below is a program to find all topological sort of a DAG, 
with time complexity as O(N * N!) and 
     space complexity as O(N!) 
                   => O(N!) space to store all topological orders, the recursion uses additional O(N) space

The program works for a graph with/without cycles. If the graph has a cycle, the output will be empty.
************************************************************************************/

#include <iostream>
#include <vector>


using namespace std;

    void dfs(vector<vector<int> >& edges, int n, vector<int>& visit, vector<int>& indegree, vector<int>& path, vector<vector<int>>& res){
        if (path.size() == n){
            res.push_back(path);
            return;
        }
        
        for (int i = 0; i < n; i++){
            if (visit[i] == 0 && indegree[i] == 0){
                for (int& ngb : edges[i])
                    indegree[ngb]--;
                visit[i] = 1;
                path.push_back(i);
                
                dfs(edges, n, visit, indegree, path, res);
                
                for (int& ngb : edges[i])
                    indegree[ngb]++;
                visit[i] = 0;
                path.pop_back();
            }
        }
    }

    vector<vector<int>> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edges(numCourses);
        vector<int> indegree(numCourses, 0);
        for (auto& p : prerequisites){
            edges[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }
        
        vector<vector<int>> res;
        vector<int> path;
        vector<int> visit(numCourses, 0);
        dfs(edges, numCourses, visit, indegree, path, res);
        
        return res;
    }


int main(){
    vector<vector<int>> prerequisites{{1,0},{2,0},{3,1},{3,2}};
    //vector<vector<int>> prerequisites{{0, 1}, {1, 2}, {2, 3}, {3, 2}, {3, 4}, {4, 5}};
    vector<vector<int>> res = findOrder(4, prerequisites);
    for (auto v : res){
        for (int& i : v)
            cout << i << " ";
        cout << endl;
    }
    
    return 0;
}
