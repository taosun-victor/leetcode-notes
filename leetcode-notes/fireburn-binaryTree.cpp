#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class TreeNode{
public:
	int val;
	TreeNode* left, *right;
	
	TreeNode(int value){
		val = value;
		left = NULL;
		right = NULL;
	}
};

// ------------------ solution 1 ---------------------------------
// dfs to establish the mapping between child nodes and parent nodes
// bfs to expand level by level
// time complexity: O(n), space complexity: O(n) --> large extra space used

void dfs(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& map){
	if (root == NULL)
		return;

	if (root->left)
		map[root->left] = root;
	if (root->right)	
		map[root->right] = root;

	dfs(root->left, map);
	dfs(root->right, map);

}

// assumption: node start is inside the tree rooted at node root
int fireburn1(TreeNode* root, TreeNode* start){
	if (root == NULL) return 0;

	unordered_map<TreeNode*, TreeNode*> map;
	dfs(root, map);

	queue<TreeNode*> q;
	unordered_set<TreeNode*> visit;
	int hours = 0;
	
	q.push(start);
	visit.insert(start);
	while(!q.empty()){
		hours++;
		int size = q.size();
		for (int i = 0; i < size; i++){
			TreeNode* curr = q.front();
			q.pop();

			if (curr->left && !visit.count(curr->left)){
				q.push(curr->left);
				visit.insert(curr->left);
			}
			if (curr->right && !visit.count(curr->right)){
				q.push(curr->right);
				visit.insert(curr->right);
			}
			if (map.count(curr) && !visit.count(map[curr])){
				q.push(map[curr]);
				visit.insert(map[curr]);
			}
		}
	}
	
	return hours;
}


// ------------- solution 2 -----------------
// dfs to print the sequence order from root to the fire start node
// two parts: dist from curr node to the start + depth of curr node
// time complexity: O(n), space complexity: O(H + H_start), avoid using O(N) to establish child-parent mapping
void dfs2(TreeNode* root, TreeNode* target, vector<TreeNode*>& vec, vector<TreeNode*>& seq){
	if (root == NULL)
		return;
		
	vec.push_back(root);
	if (root == target){
		seq = vec;
		return;
	}
	
	dfs2(root->left, target, vec, seq);
	dfs2(root->right, target, vec, seq);
	
	vec.pop_back();
}

int getDepth(TreeNode* root){
	if (root == NULL)
		return 0;
		
	return 1 + max(getDepth(root->left), 
	               getDepth(root->right));
}

int fireburn2(TreeNode* root, TreeNode* start){
	vector<TreeNode*> vec;
	vector<TreeNode*> seq;
	dfs2(root, start, vec, seq);
	
	int hours = 0;
	for (int i = 0; i < seq.size(); i++){
		int time = seq.size() - i;
		if (i < seq.size() - 1){
			if (seq[i]->left == seq[i + 1])
				time += getDepth(seq[i]->right);
			else
				time += getDepth(seq[i]->left);
		}
		else{
			time += getDepth(seq[i]) - 1;
		}
		hours = max(hours, time);
	}
	return hours;
}

// ---------------- Solution 3 ---------------------
int burnUp(TreeNode* root, TreeNode* start, int& upTime){
	if (root == NULL)
		return 0;
	if (root == start)
		return -1;
		
	int l = burnUp(root->left, start, upTime);
	int r = burnUp(root->right, start, upTime);
	
	//cout << "root: " << root->val << " left: " << l << " right: " << r << endl;
	
	if (l >= 0 && r >= 0)
		return 1 + max(l, r);
	else if (l < 0 && r >= 0){
		upTime = max(upTime, -l + r + 1);
		return l - 1;
	}
	else if (l >= 0 && r < 0){
		upTime = max(upTime, l - r + 1);
		return r - 1;
	}
	else
		return 100;
}

int fireburn3(TreeNode* root, TreeNode* start){
	int upTime = 0;
	burnUp(root, start, upTime);
	
	int downTime = getDepth(start);
	
	return max(upTime, downTime);
}

int main(){
	TreeNode* root = new TreeNode(10);
	root->left = new TreeNode(5);
	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(7);
	
	root->right = new TreeNode(25);
	root->right->left = new TreeNode(21);
	root->right->left->left = new TreeNode(20);
	root->right->left->left->left = new TreeNode(18);
	root->right->left->left->left->left = new TreeNode(17);
	root->right->left->left->left->right = new TreeNode(19); 
	
	root->right->left->right = new TreeNode(24);
	TreeNode* start = root->right->left->right;
	root->right->left->right->left = new TreeNode(23);
	root->right->left->right->right = new TreeNode(26);
	
	root->right->right = new TreeNode(30);
	
	cout << "sol 1: " << fireburn1(root, start) << endl;
	cout << "sol 2: " << fireburn2(root, start) << endl;
	cout << "sol 3: " << fireburn3(root, start) << endl;
	
	// should have cleaned the heap memories
	return 0;
}
/*
           10(4)
          /   \
         5(5)  25
      /  \    /   \    
    2(6) 7   21   30
           /   \
		  20   24(1)
		 /    /  \
		18   23  26
	   /  \
	  17  19  	  
*/


