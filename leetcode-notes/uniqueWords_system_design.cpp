class FreqOnes {
    private:
	list<string> freqOne;
        unordered_set<string> set;
	unordered_map<string, list<string>::iterator> map
        GStreaming gst;

    public:
	FreqOnes(GStreaming _gst) {
            gst = _gst;
        }

	void accumulate(){
	    while(!gst.isEnd()){
		string curr = gst.getNext();
	    	if (!set.count(curr)){
		    set.insert(curr);	
	            freqOne.push_back(curr);
		    map[curr] = freqOne.back();
		}
	        else{
		    freqOne.erase(map[curr]);
		    map.erase(curr);
		}
	    }
	}

	list<string> getUniqueWords(){
	    return freqOne;
	}
};

int main(){
    GStreaming<string> gst{"Google", "Facebook", "Google", "Facebook", "LinkedIn","Facebook", "Apple"};
    FreqOne f(gst);
    f.accumulate();
    list<string> res = f.getUniqueWords();

    list<string> expected{"LinkedIn", "Apple"};
    assert(res.size() == expected.size());
    for (int i = 0; i < res.size(); i++)
        assert(res[i] == expected[i]);

    return 0;
}

