#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>

#include "filter.h"
#include "entry.h"

using namespace std;

class FileSystem {
private:
    Directory* root;
    
    vector<string> tokenize(const string& path){
        istringstream iss(path);
        string token;
        vector<string> dirs;
        
        while(getline(iss, token, '/'))
            dirs.push_back(token);
        return dirs;
    }
    
    Entry* findEntry(vector<string>& dirs){
        Entry* curr = root;
        for (string dir : dirs){
            if (((Directory*)curr)->findChild(dir) != NULL)
                curr = ((Directory*)curr)->findChild(dir);
        }
        return curr;
    }
    
public:
    FileSystem() {
        root = new Directory("Root");
    }
    
    void mkdir(string path) {
        vector<string> dirs = tokenize(path);
        Entry* curr = root;
        for (string& dir : dirs){
            if (((Directory*)curr)->findChild(dir) == NULL){
                ((Directory*)curr)->addChild(new Directory(dir));
            }
            curr = ((Directory*)curr)->findChild(dir);
        }
    }
    
    void addFile(string filePath, int fileSize) {
        vector<string> dirs = tokenize(filePath);
        string fileName = dirs.back();
        dirs.pop_back();
        
        Entry* curr = findEntry(dirs);
        
        ((Directory*)curr)->addChild(new File(fileName, fileSize));
    }
    
    vector<string> searchTargetFiles(Filter& filter){
    	vector<string> res;
    	root->search(root, filter, res);
    	return res;
	}
};

#endif
