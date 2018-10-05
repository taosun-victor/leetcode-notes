#include <iostream>
#include <vector>
#include <climits>
#include <chrono> 

using namespace std;
using namespace std::chrono;

struct TreeNode {
    int val;
    int index;
    int minIndex;
    TreeNode *left, *right;
    
    TreeNode(int v, int i, int minI){
        val = v;
        index = i;
	minIndex = minI;
        left = NULL;
        right = NULL;
    }        
};

TreeNode * insert(TreeNode *& subRoot, int v, int idx, int& mn){
    if (subRoot == NULL){
        subRoot = new TreeNode(v, idx, idx);
    }
    else if (v < subRoot->val){
        subRoot->minIndex = idx;
        subRoot->left = insert(subRoot->left, v, idx, mn);
    }
    else if (v > subRoot->val){
        mn = min(mn, subRoot->minIndex);
	subRoot->right = insert(subRoot->right, v, idx, mn);
    }
    else{
        //subRoot->index = idx;
	mn = min(mn, min(subRoot->minIndex, subRoot->index));
	subRoot->minIndex = idx;
    }
    
    return subRoot;
}

vector<int> countSmaller(vector<int>& prices) {
    cout << "original: ";
    for (auto p : prices)
	cout << p << " ";
    cout << endl;

    int n = prices.size();
    vector<int> final_price(n), discount(n);
    TreeNode * root = NULL;
    for (int i = n-1; i >= 0; --i){
        int mn = INT_MAX;
	insert(root, prices[i], i, mn);
	discount[i] = (mn == INT_MAX) ? 0 : prices[mn];
    }
    cout << "discounts: ";
    for (auto d : discount)
	cout << d << " ";
    cout << endl;

    for (int i=0; i<n; ++i)
	final_price[i] = prices[i] - discount[i];

    cout << "final: ";
    for (auto o : final_price)
        cout << o << " ";
    cout << endl;

    return final_price;
}

int main() {
    //vector<int> input({5, 1, 3, 4, 6, 2});
    //vector<int> input({1, 3, 3, 2, 5});
    //vector<int> input({1, 3, 2, 5, 3});
    vector<int> input({1, 4, 1, 1, 4, 3, 5});
    //vector<int> input({3, 1, 3, 1, 1, 1});
    
    auto start = high_resolution_clock::now();
    vector<int> finalPrices = countSmaller(input);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken: "
         << duration.count() << " microseconds" << endl; 
    return 0;
}
