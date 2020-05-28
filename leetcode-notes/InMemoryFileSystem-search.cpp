#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//--------------------------- Implementation of File and Directory classes -----------------------
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
    //unordered_map<string, Entry*> children;
public:
	unordered_map<string, Entry*> children;
	
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
};

//-------------------------- Implementation of Filter classes ------------------------------
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


// ---------------------- Implementation of FileSystem class -----------------------------
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
    
    void search(Entry* entry, Filter& filter, vector<string>& res){
    	if (entry->isFile()){
    		if (filter.isValid((File*)entry))
    			res.push_back(entry->getName());
    		return;
		}
		
		// here we need to traverse the "children" field of a "directory".
		// currently make "children" filed public in "directory" class
		// any better ideas?
		for (auto m : ((Directory*)entry)->children)
			search(m.second, filter, res);
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
    	search(root, filter, res);
    	return res;
	}
};

int main() {
	FileSystem fs;
	
	// ----- build the tree structure for the file system ----
	fs.mkdir("/a/b/c");
	fs.mkdir("/a/b/d");
	fs.mkdir("/a/k");
	
	fs.addFile("/a/b/file1.txt", 10);
	fs.addFile("/a/b/node2.txt", 5);
	fs.addFile("/a/b/c/file3.txt", 4);
	fs.addFile("/a/b/c/node4.txt", 16);
	fs.addFile("/a/b/d/node5.txt", 15);
	fs.addFile("/a/k/file6.txt", 11);
	fs.addFile("/a/k/node7.txt", 3);
	fs.addFile("/a/file8.txt", 20);
	
    // ---------------Test size filter ----------------	
	sizeFilter sF(10);
	vector<string> v = fs.searchTargetFiles(sF);
	cout << "All files with size no smaller than 10: ";
	for (string str : v)
		cout << str << ", ";
	cout << endl;
	
	// --------------- Test name filter ------------------
	prefixFilter pF("file");
	v = fs.searchTargetFiles(pF);
	cout << "All files whose name has prefix of 'file': ";
	for (string str : v)
		cout << str << ", ";
	cout << endl;	
	
	//--------------- Test And filter -----------------
	AndFilter aF(&sF, &pF);
	v = fs.searchTargetFiles(aF);
	cout << "All files with size >= 10 AND name with prefix 'file' : ";
	for (string str : v)
		cout << str << ", ";
	cout << endl;
	
	//------------- Test Or filter ---------------------
	OrFilter oF(&sF, &pF);
	v = fs.searchTargetFiles(oF);
	cout << "All files with size >= 10 OR name with prefix 'file' : ";
	for (string str : v)
		cout << str << ", ";
	cout << endl;		
	
	
	return 0;
}


