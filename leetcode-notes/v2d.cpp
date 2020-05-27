#include <iostream>
#include <vector>

using namespace std;

class v2D {
private:
	vector<vector<int>> v;
public:
	v2D(vector<vector<int>>& D){
		v = D;
	}
	
	void update(int i, int j, int val){
		if (i >= v.size() || j >= v[i].size())
			cout << "folks aluru invalid" << endl;
		else
			v[i][j] = val;
	}
	
	void printV(){
		for (int i = 0; i < v.size(); i++){
			for (int j = 0; j < v[i].size(); j++)
				cout << v[i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}
};


void print2D(vector<vector<int>>& f){
	cout << "-- print 2D---" << endl;
	for (int i = 0; i < f.size(); i++){
		for (int j = 0; j < f[i].size(); j++)
			cout << f[i][j] << " ";
		cout << endl;
	}
	cout << "-- print 2D finish---" << endl;
}

int main(){
	vector<vector<int>> D{{1, 2, 3}, {4, 5, 6, 7}, {8, 9}};
	v2D folks(D);
	folks.printV();
	folks.update(1, 2, 100);
	folks.printV();
	
	print2D(D);
	
	return 0;
}
