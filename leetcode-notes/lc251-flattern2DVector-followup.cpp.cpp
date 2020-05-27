#include <iostream>
#include <vector>

using namespace std;

class ZigzagIterator {
private:
    vector<vector<int>> v;
    vector<int> indices;
    int curr;
    bool straight;
public:
    ZigzagIterator(vector<vector<int>>& V) {
    	straight = false;
        v = V;
        for (int i = 0; i < v.size(); i++)
        	indices.push_back(0);
        
        curr = 0;
        while(curr < v.size() && v[curr].empty())
            curr++;
    }

    int next() {
        if (hasNext() == false){
            return INT_MIN;
        }
        int val = v[curr][indices[curr]];
        indices[curr]++;
        if (straight) return val;
        
        int prev = curr;
        for (int i = 1; i <= v.size(); i++){
            int j = (curr + i) % v.size();
            if (indices[j] < v[j].size()){
                curr = j;
                break;
            }
        }
        if (curr == prev)
        	straight = true;
        
        return val;
    }

    bool hasNext() {
        int hasNext = false;
        for (int i = 0; i < indices.size(); i++)
            hasNext = (hasNext || indices[i] < v[i].size());
        return hasNext;
    }
};

int main() {
	vector<vector<int>> v{
	                    	{1, 2, 3, 4, 5}, 
	                      	{}, 
						    {7, 8, 9}, 
						    {10, 11, 12, 13, 14, 15, 16, 17, 18, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110},
						    {20, 21, 22, 23, 24, 25}
						};
	ZigzagIterator zig(v);
	while(zig.hasNext())
		cout << zig.next() << " ";
	cout << endl;
	
	return 0;
}
