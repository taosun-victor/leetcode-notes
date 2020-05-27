#include <iostream>
#include <stack>

using namespace std;

class TreeNode{
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	
	TreeNode(int value){
		val = value;
		left = NULL; 
		right = NULL;
	}		
};

class preorderIterator{
private:
	stack<TreeNode*> st;

public:
	preorderIterator(TreeNode* root){ // assuming root is not NULL
			st.push(root);
	}

	int next(){
		TreeNode* curr = st.top();
		st.pop();
	
	if (curr->right)
		st.push(curr->right);
	if (curr->left)
		st.push(curr->left);
	return curr->val;
	}

	bool hasNext(){
		return !st.empty();
	}
};


int main(){
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);
	
	root->right = new TreeNode(3);
	root->right->left = new TreeNode(6);
	root->right->right = new TreeNode(7);
	
	preorderIterator poi(root);
	while(poi.hasNext())
		cout << poi.next() << " ";
	cout << endl;
	
	delete root->left->left;
	delete root->left->right;
	delete root->left;
	
	delete root->right->left;
	delete root->right->right;
	delete root->right;
	
	delete root;
	
	return 0;
}

