// this is a compressed version of Trie with C++, reference:
// http://theoryofprogramming.com/2016/11/15/compressed-trie-tree/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie {
public:
    /** Initialize your data structure here. */
    class TrieNode {
        public:
	    bool isWord;
	    vector<TrieNode *> children;
	    vector<string> edgeLabel;

	    TrieNode(){
	        isWord = false;
		children = vector<TrieNode *>(26, NULL);
		edgeLabel = vector<string>(26, "");
	    }
    };
    
    TrieNode * root;
    
    
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word){
        TrieNode * tmp = root;
	    int i = 0;

	    while(i < word.size() && tmp->edgeLabel[word[i] - 'a'] != ""){
	        int idx = word[i] - 'a', j = 0;
	        string label = tmp->edgeLabel[idx];

	        while(j < label.size() && i < word.size() && label[j] == word[i]){
	            ++i; 
                ++j;
	        }
	
	        if (j == label.size()){
	            tmp = tmp->children[idx];
            }
	        else {
	            if (i == word.size()){  // inserting a prefix of exisiting word, 
                                        // have "facebook" and insert "face"
		            TrieNode * existingChild = tmp->children[idx];
		            TrieNode * newChild = new TrieNode();
		            newChild->isWord = true;
		            string remainingLabel = label.substr(j);

		            tmp->edgeLabel[idx] = label.substr(0, j);
		            tmp->children[idx] = newChild;
		            newChild->children[remainingLabel[0] - 'a'] = existingChild;
		            newChild->edgeLabel[remainingLabel[0] - 'a'] = remainingLabel;
		        }
		        else {      // inserting word which has a partial match with existing word, 
                            // have "therefore" and "therein", insert "thereis"
		            string remainingLabel = label.substr(j);
		            TrieNode * newChild = new TrieNode();
		            string remainingWord = word.substr(i);
		            TrieNode * trav = tmp->children[idx];

		            tmp->edgeLabel[idx] = label.substr(0, j);
		            tmp->children[idx] = newChild;
		            newChild->edgeLabel[remainingLabel[0] - 'a'] = remainingLabel;
		            newChild->children[remainingLabel[0] - 'a'] = trav;
		            newChild->edgeLabel[remainingWord[0] - 'a'] = remainingWord;
		            newChild->children[remainingWord[0] - 'a'] = new TrieNode();
		            newChild->children[remainingWord[0] - 'a']->isWord = true;
		        }
	    	
		        return;
	        }
	    }

	    if (i < word.size()){       // inserting new node for new word, totally new
                                    // have "for" and "do", insert "while"
	        tmp->edgeLabel[word[i] - 'a'] = word.substr(i);
	        tmp->children[word[i] - 'a'] = new TrieNode();
	        tmp->children[word[i] - 'a']->isWord = true;
	    }
	    else{ // inserting "there" when "therein" and "thereafter" are existing, already break up
	        tmp->isWord = true;
	    }
	    
        return;
    }

    /** Returns if the word is in the trie. */
    bool search(string word){
    	int i = 0;
        TrieNode *tmp = root;

        while (i < word.size() && tmp->edgeLabel[word[i] - 'a'] != "") {
            int idx = word[i] - 'a';
            string label = tmp->edgeLabel[idx];
            int j = 0;

            while (i < word.size() && j < label.size()) {
                if (word[i] != label[j]) {
                    return false;   // character mismatch
                }
                ++i;
                ++j;
            }

            if (j == label.size() && i <= word.size()) {
                tmp = tmp->children[idx];    // traverse further to next level
            } 
            else {
                // edge label is larger than target word
                // only has prefix, while the prefix is not inserted as a word
                // searching for "face" when tree has "facebook"
                return false;
            }
        }

        // target word fully traversed and current node is a word ending
        return i == word.size() && tmp->isWord == true; 
    }
    
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix){
        int i = 0;
        TrieNode *tmp = root;

        while (i < prefix.size() && tmp->edgeLabel[prefix[i] - 'a'] != "") {
            int idx = prefix[i] - 'a';
            string label = tmp->edgeLabel[idx];
            int j = 0;

            while (i < prefix.size() && j < label.size()) {
                if (prefix[i] != label[j]) {
                    return false;   // character mismatch
                }
                ++i;
                ++j;
            }

            if (j == label.size() && i <= prefix.size()) {
                tmp = tmp->children[idx];    // traverse further
            } 
            else {
                // edge label is larger than target word, which is fine
                return true;
            }
        }

        return i == prefix.size();
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

int main(){
    Trie *obj = new Trie();
    obj->insert("facebook");
    obj->insert("face");

    obj->insert("therefor");
    obj->insert("therein");
    obj->insert("thereis");
    
    obj->insert("for");
    obj->insert("do");
    obj->insert("while");
  
    obj->insert("there");

    cout << obj->search("face") << endl;
    cout << obj->search("facebook") << endl;
    cout << obj->search("there") << endl;
    cout << obj->search("therefor") << endl;
    cout << obj->search("thereis") << endl;
    
    cout << obj->startsWith("faceb") << endl;
    cout << obj->startsWith("the") << endl;
    cout << obj->startsWith("therei") << endl;

    return 0;
}
