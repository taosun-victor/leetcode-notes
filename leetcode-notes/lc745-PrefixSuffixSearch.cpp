#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie {
private:
    class TrieNode{
    public:    
        bool isWord;
        int index;
        TrieNode * children[27];
        
        TrieNode(){
            isWord = false;
            index = -1;
            for (int i=0; i<27; i++)
                children[i] = NULL;
        }
    };
    
    TrieNode * root;
    
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word, int index) {
        TrieNode * tmp = root;
        for (int i=0; i<word.size(); i++){
            int idx = word[i] - 'a';
            if (tmp->children[idx] == NULL)
                tmp->children[idx] = new TrieNode();
            tmp = tmp->children[idx];
            tmp->index = index;
        }
        tmp->isWord = true;
    }
    
    int startsWith(string all_prefix) {    
        TrieNode * tmp = root;
        for (int i=0; i<all_prefix.size(); i++){
            int idx = all_prefix[i] - 'a';
            if (tmp->children[idx] == NULL) return -1;
            tmp = tmp->children[idx];
        }
        return tmp->index;
    }
};


class WordFilter {
private:
    Trie trie;
    
public:
    // here used a trick with '{', since the ASCII code
    // for '{' is 27, we could use children['{' - 'a']
    // to find the position
    WordFilter(vector<string> words) {
        for (int i=0; i<words.size(); ++i){
            string w = words[i];
	    // will be able to include all prefix
            string key = '{' + w;
            trie.insert(key, i);
            for (int j=0; j<w.size(); ++j){
		// find all suffix one by one
                key = w[w.size()-j-1] + key;
                trie.insert(key, i);
            }
        }
    }
    
    int f(string prefix, string suffix) {
        return trie.startsWith(suffix + "{" + prefix);        
    }
};


int main(){
    vector<string> words({"apple", "aple", "Hello", "alle"});
    WordFilter *obj = new WordFilter(words);
    cout << obj->f("a", "le") << endl;
    return 0;
}
