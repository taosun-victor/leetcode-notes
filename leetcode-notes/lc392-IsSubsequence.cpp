//*********************** sol 1 linear scan O(T) ********************
class Solution1 {
public:
    bool isSubsequence(string s, string t) {
        int i = 0;
        for (int j = 0; j < t.size(); j++){
            if (s[i] == t[j])
                i++;
        }
        return i == s.size();
    }
};


//*********************** sol 2 binary search O(S * logT) ************
// this is to solve the follow up question where multiple s0, s1, s2 ... are coming
class Solution2 {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>> map(26);
        for (int i = 0; i < t.size(); i++)
            map[t[i] - 'a'].push_back(i);
        int pre = -1;
        for (int j = 0; j < s.size(); j++){
            vector<int>& indices = map[s[j] - 'a'];
            auto it = upper_bound(indices.begin(), indices.end(), pre);
            if (it == indices.end()) 
                return false;
            pre = *it;
        }
        return true;
    }
};
