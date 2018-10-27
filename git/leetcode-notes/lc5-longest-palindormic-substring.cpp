// Manache's algorithms -> O(n)
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string longestPalindromicSubstring(string s){
    string ps = "$#";
    for (auto ch : s){
        ps += ch;
	ps += '#';
    }

    vector<int> p(ps.size(), 0);
    int id = 0, mx = 0;
    int start = 0, len = 0;

    for (int i=0; i<ps.size(); ++i){
        p[i] = (mx > i) ? min(p[2*id - 1], mx - i) : 1;
	while(ps[i - p[i]] == ps[i + p[i]])
	    ++p[i];

	if (i + p[i] > mx){
	    id = i;
	    mx = i + p[i];
	}

	if (p[i] - 1 > len){
	    start = (i - p[i]) / 2;
	    len = p[i] - 1;
	}
    }

    return s.substr(start, len);
}


int main() {
    cout << longestPalindromicSubstring("io9aabceeueecbaaiojnh") << endl;
    return 1;
}
