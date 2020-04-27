//***************************** solution 1 KMP *****************************
class Solution1 {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if (m < n) return -1;
        if (n == 0) return 0;
        
        vector<int> next = computePrefix(needle);
        int k = 0;
        for (int j = 0; j < m; j++){
            while(k > 0 && needle[k] != haystack[j])
                k = next[k];
            if (needle[k] == haystack[j])
                k++;
            if (k == n)
                return j - n + 1;
        }
        return -1;
    }
    
    vector<int> computePrefix(string& needle){
        int n = needle.size();
        vector<int> next{0, 0};
        int k = 0;
        for (int i = 1; i < n; i++){
            while(k > 0 && needle[k] != needle[i])
                k = next[k];
            if (needle[k] == needle[i])
                k++;
            next.push_back(k);
        }
        for (int& i : next)
            cout << i << " ";
        cout << endl;
        return next;
    }
};


//**************************** Solution 2 Rabin-Karp *******************
class Solution2 {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if (m < n) return -1;
        if (n == 0) return 0;
        
        int base = 26;
        long M = pow(2, 31), hash = 0, hashRef = 0;
        long baseN = 1;
        for (int i = 0; i < n; i++){
            hash = (hash * base + haystack[i] - 'a') % M;
            hashRef = (hashRef * base + needle[i] - 'a') % M;
            baseN = (baseN * base) % M;
        }
        if (hash == hashRef) return 0;
        
        for (int i = 1; i <= m - n; i++){
            hash = (hash * base - (haystack[i - 1] - 'a') * baseN + (haystack[i + n - 1] - 'a')) % M;
            if (hash == hashRef)
                return i;
        }
        return -1;
    }
};
