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

// return the root node of the whole subtree after deleting all one-child nodes
// this way of implementation is not clear in semantics
TreeNode* deleteHalf(TreeNode* root){
	if (root == NULL)
		return NULL;

	root->left = deleteHalf(root->left);
	root->right = deleteHalf(root->right);

	// one child null, the other not null
	if (root->left && !root->right)
		return root->left;
	if (!root->left && root->right)
		return root->right;
		
	// both children are null, or both are not null
	return root;
}


TreeNode* deleteHalf2(TreeNode* root){
	if (root == NULL)
		return NULL;

	TreeNode* Left = deleteHalf(root->left);
	TreeNode* Right = deleteHalf(root->right);

	// one child null, the other not null
	if (Left && !Right)
		return Left;
	if (!Left && Right)
		return Right;
		
	// both children are null, or both are not null
	root->left = Left;
	root->right = Right;
	return root;
}

void inOrderPrint(TreeNode* root){
	if (root == NULL)
		return;
		
	inOrderPrint(root->left);
	
	cout << root->val << ", ";
	
	inOrderPrint(root->right);
}

int main(){
	TreeNode* root = new TreeNode(10);
	
	root->left = new TreeNode(5);
	root->left->left = new TreeNode(6);
	root->left->left->left = new TreeNode(2);
	root->left->left->right = new TreeNode(8);
	
	root->right = new TreeNode(12);
	root->right->right = new TreeNode(14);
	root->right->right->right = new TreeNode(19);
	
	inOrderPrint(root);
	cout << endl;
	
	root = deleteHalf2(root);
	inOrderPrint(root);
	
}

