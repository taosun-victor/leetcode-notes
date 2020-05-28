#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include "filter.h"

using namespace std;

class Entry {
private:
    string name;
public:
    Entry(const string& name){
        this->name = name;
    }
    string getName(){
        return name;
    }
    virtual bool isFile() = 0;    
};

class File : public Entry {
private:
    int size;
public:
    File(string name, int size) : Entry(name){
        this->size = size;
    }
    
    bool isFile() override {
        return true;
    }
    
	int getSize(){
		return this->size;
	}
};

class Directory : public Entry {
private:
	//Problem here: we set "children" field as a public member, which might not be good ...
    unordered_map<string, Entry*> children;
public:
	//unordered_map<string, Entry*> children;
	
    Directory(string name) : Entry(name) {}
    
    bool isFile() override {
        return false;
    }
    
    Entry* findChild(string childName) {
        if (children.count(childName))
            return children[childName];
        return NULL;
    }
    
    void addChild(Entry* child){
        children[child->getName()] = child;
    }
    
    void search(Entry* entry, Filter& filter, vector<string>& res){
    	if (entry->isFile()){
    		if (filter.isValid((File*)entry))
    			res.push_back(entry->getName());
    		return;
		}
		
		for (auto m : ((Directory*)entry)->children)
			search(m.second, filter, res);
	}
};

#endif
