// this is an implementation for search auto complete system with C++
// the data structure used is Trie
// Unfortunately on Leetcode it says "Memory Limit Exceeded"
// by using java it is OK though

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

class AutoCompleteSystem {
private:
    class Compare {
        public:
        bool operator() (pair<string, int>& a, pair<string, int>& b){
            return a.second < b.second || (a.second == b.second && a.first > b.first);
        }
    };
    
    class TrieNode{
        public:
	    unordered_map<char, TrieNode *> children;
	    unordered_map<string, int> counts;

	    TrieNode() {
	        for (int i=0; i<26; ++i)
	            children['a' + i] = NULL;
	    }
    }; 
    
    TrieNode* root;
    string prefix;

    void insert(string sentence, int times){
        TrieNode *curr = root;
	    for (char ch : sentence){
	        if (!curr->children[ch])
	            curr->children[ch] = new TrieNode();
	        curr = curr->children[ch];
	        curr->counts[sentence] += times;
	    }
    }

public:
    AutoCompleteSystem(vector<string> sentences, vector<int> times) {
        root = new TrieNode();
	    prefix = "";
	    for (int i=0; i<sentences.size(); ++i)
	        insert(sentences[i], times[i]);
    }
    
    vector<string> input(char c) {
        if (c == '#'){
            insert(prefix, 1);
            prefix = "";
            return vector<string>();
        }
        
        prefix += c;
	    TrieNode *curr = root;
            for (auto ch : prefix){
	        if (!curr->children[ch])
		        return vector<string>();
	        curr = curr->children[ch];
	    }

        priority_queue<pair<string, int>, vector<pair<string, int>>, Compare> q;
        
        for (auto f : curr->counts)
            q.push(f);
        
        vector<string> res;
        for (int i=0; i<3; i++){
            if (!q.empty()){
	        res.push_back(q.top().first);
                q.pop();
	        }
        }
        return res;
    }
};

void printVec(vector<string> v){
    for (auto a : v)
        cout << a << "||";
    cout << endl;
}

int main() {
    vector<string> sentences({"i love you","island","i love leetcode"});
    vector<int> times({5,3,2,2});
    AutoCompleteSystem *obj = new AutoCompleteSystem(sentences, times);
    
    vector<string> round1 = obj->input('i');
    vector<string> round2 = obj->input(' ');
    vector<string> round3 = obj->input('a');
    vector<string> round4 = obj->input('#');

    printVec(round1);
    printVec(round2);
    printVec(round3);
    printVec(round4);

    return 0;
}
