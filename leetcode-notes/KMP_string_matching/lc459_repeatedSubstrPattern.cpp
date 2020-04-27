class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();
        vector<int> next(n + 1, 0);
        int j = 0;
        for (int i = 1; i < s.size(); i++){
            while(j > 0 && s[j] != s[i])
                j = next[j];
            if (s[j] == s[i])
                j++;
            next[i + 1] = j;
        }
        return next[n] && next[n] % (n - next[n]) == 0;
    }
};
