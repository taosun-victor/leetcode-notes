class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        vector<int> nextB = computePrefix(B);
        string a = A;
        int cnt = 1;
        while(a.size() < B.size()){
            a += A;
            cnt++;
        }
        if (isSubstring(a, B, nextB))
            return cnt;
        a += A;
        if (isSubstring(a, B, nextB))
            return cnt + 1;
        return -1;
    }
    
    bool isSubstring(string& AA, string& B, vector<int>& nextB){
        int k = 0;
        for (int j = 0; j < AA.size(); j++){
            while(k > 0 && B[k] != AA[j])
                k = nextB[k];
            if (B[k] == AA[j])
                k++;
            if (k == B.size())
                return true;
        }
        return false;
    }
    
    vector<int> computePrefix(string& str){
        vector<int> next{0, 0};
        int k = 0;
        for (int i = 1; i < str.size(); i++){
            while(k > 0 && str[k] != str[i])
                k = next[k];
            if (str[k] == str[i])
                k++;
            next.push_back(k);
        }
        return next;
    }
};
