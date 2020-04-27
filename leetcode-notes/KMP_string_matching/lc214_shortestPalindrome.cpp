class Solution {
public:
    string shortestPalindrome(string s) {
        string r(s.rbegin(), s.rend());
        string t = s + "#" + r;
        int n = t.size();
        vector<int> next(n + 1, 0);
        
        int k = 0;
        for (int i = 1; i < n; i++){
            while(k > 0 && t[k] != t[i])
                k = next[k];
            if (t[k] == t[i])
                k++;
            next[i + 1] = k;
        }
        return string(s.rbegin(), s.rbegin() + s.size() - next[n]) + s;
    }
};
