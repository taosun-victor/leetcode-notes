#include iostream
#include <stack>

using namespace std;

class BTInorderIterator{
private:
	stack<TreeNode*> st;

	void traverseLeft(TreeNode* node){ // assuming root is not NULL
		while(node){
			st.push(node);
			node = node->left;
		}
	}

public:
	BTInorderIterator(TreeNode* root){
		traverseLeft(root);
	}

	int next(){
		TreeNode* curr = st.top();
		st.pop();
		traverseLeft(curr->right);
		return curr->val;
	}
	
	bool hasNext(){
		return !st.empty();
	}
};


//Binary tree inorder traversal using Morris method with O(1) extra space 
vector<int> inorderTraversal(TreeNode* root){
	vector<int> res;
	if (root == NULL) return res;

	TreeNode* curr = root;
	while(curr){
		if (curr->left == NULL){
			res.push_back(curr->val);
			curr = curr->right;
		}
		else{
			TreeNode* pre = curr->left;
			while(pre->right != NULL && pre->right != curr)
				pre = pre->right;
			if (pre->right == NULL){
				pre->right = curr;
				curr = curr->left;
			}
			else{
				pre->right = NULL;
				res.push_back(curr->val);
				curr = curr->right;
			}
		}
	}
	return res;
}



//Extension: Binary tree Post order Iterator
class BTPostorderIterator {
private:
	stack<TreeNode*> st;

	void traverseNextLeaf(TreeNode* node){ // assuming root is not NULL
		while(node){
			st.push(node);
			if (node->left)
				node = node->left;
			else
				node = node->right;
		}			
	}

public:
	BTPostorderIterator(TreeNode* root){
		traverseNextLeaf(root);
	}

	int next(){
		TreeNode* curr = st.top();
		st.pop();
	
		if (!st.empty()){
			TreeNode* top = st.top();
			if (curr == top->left)
				traverseNextLeaf(top->right);
		}
		return curr->val;
	}
	
	bool hasNext(){
		return !st.empty();
	}
};


//Extension: Binary Tree Postorder Traversal with iteration
vector<int> postorderTraversal(TreeNode* root){
	vector<int> res;
	if (root == NULL) return res;

	TreeNode* curr = root;
	stack<TreeNode*> st;
	while(!st.empty() || curr){
		while(curr){
			st.push(curr);
			if (curr->left)
				curr = curr->left;
			else
				curr = curr->right;
		}
		curr = st.top();
		st.pop();
		res.push_back(curr->val);

		if (!st.empty() && curr == st.top()->left)
			curr = st.top()->right;
		else
			curr = NULL;
	}
	return res;
}


//Next extension: Binary tree Preorder iterator
class BTPreorderIterator {
private:
	stack<TreeNode*> st;

public:
	BTPostorderIterator(TreeNode* root){ // assuming root is not NULL
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


