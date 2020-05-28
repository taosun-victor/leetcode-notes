#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include "entry.h"

using namespace std;

class Filter {
public:
	virtual bool isValid(File* file) = 0;		
};

class sizeFilter : public Filter {
private:
	int targetSize;
public:
	sizeFilter(int targetSize){
		this->targetSize = targetSize;
	}
	
	bool isValid(File* file) override {
		return file->getSize() >= targetSize;
	}
};

class prefixFilter : public Filter {
private:
	string prefix;
public:
	prefixFilter(string prefix){
		this->prefix = prefix;
	}
	
	bool isValid(File* file) override {
		string name = file->getName();
		for (int i = 1; i <= name.size(); i++){
			if (name.substr(0, i) == prefix)
				return true;
		}
		return false;
	}
};

class AndFilter : public Filter {
private:
	Filter* f1;
	Filter* f2;
public:
	AndFilter(Filter* f1, Filter* f2){
		this->f1 = f1;
		this->f2 = f2;
	}
	
	bool isValid(File* file) override {
		return f1->isValid(file) && f2->isValid(file);
	}
};


class OrFilter : public Filter {
private:
	Filter* f1;
	Filter* f2;
public:
	OrFilter(Filter* f1, Filter* f2){
		this->f1 = f1;
		this->f2 = f2;
	}
	
	bool isValid(File* file) override {
		return f1->isValid(file) || f2->isValid(file);
	}
};

#endif
