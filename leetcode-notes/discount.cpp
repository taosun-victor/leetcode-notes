#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    int index;
    TreeNode *left, *right;
    
    TreeNode(int v, int i){
        val = v;
        index = i;
        left = NULL;
        right = NULL;
    }        
};

TreeNode * insert(TreeNode *& subRoot, int v, int idx, int& mn){
    if (subRoot == NULL){
        subRoot = new TreeNode(v, idx);
    }
    else if (v < subRoot->val){
        subRoot->index = idx;
        subRoot->left = insert(subRoot->left, v, idx, mn);
    }
    else if (v > subRoot->val){
        mn = min(mn, subRoot->index);
	subRoot->right = insert(subRoot->right, v, idx, mn);
    }
    else{
        subRoot->index = idx;
	mn = idx;
    }
    
    return subRoot;
}

vector<int> countSmaller(vector<int>& prices) {
    int n = prices.size();
    vector<int> final_price(n), discount(n);
    TreeNode * root = NULL;
    for (int i = n-1; i >= 0; --i){
        int mn = INT_MAX;
	insert(root, prices[i], i, mn);
	discount[i] = (mn == INT_MAX) ? 0 : prices[mn];
    }
    for (auto d : discount)
	cout << d << " ";
    cout << endl;

    for (int i=0; i<n; ++i)
	final_price[i] = prices[i] - discount[i];

    for (auto o : final_price)
        cout << o << " ";
    cout << endl;

    return final_price;
}

int main() {
    //vector<int> input({5, 1, 3, 4, 6, 2});
    vector<int> input({1, 3, 3, 2, 5});
    vector<int> finalPrices = countSmaller(input);
    return 0;
}
