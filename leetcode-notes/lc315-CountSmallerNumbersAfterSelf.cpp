#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    int smaller;
    TreeNode *left, *right;
    
    TreeNode(int v, int s){
        val = v;
        smaller = s;
        left = NULL;
        right = NULL;
    }        
};

int insert(TreeNode *& subRoot, int v){
    if (subRoot == NULL){
        subRoot = new TreeNode(v, 0);
        return 0;
    }
    if (v < subRoot->val){
        subRoot->smaller += 1;
        return insert(subRoot->left, v);
    }
    
    return insert(subRoot->right, v) + subRoot->smaller + (v == subRoot->val ? 0 : 1);
}

vector<int> countSmaller(vector<int>& nums) {
    vector<int> res(nums.size());
    TreeNode * root = NULL;
    for (int i = nums.size() - 1; i >= 0; --i){
        res[i] = insert(root, nums[i]);
    }
    return res;
}

int main() {
    vector<int> input({5, 2, 6, 1});
    vector<int> output = countSmaller(input);
    for (auto o : output)
        cout << o << " ";
    cout << endl;
}
