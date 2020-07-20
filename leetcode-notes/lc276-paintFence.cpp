#include <iostream>
#include <vector>

using namespace std;

/**********************************************************************************
*  Problem Statement: Paint N pieces of woods with two colors, white and black.   *
*  The only constraint is that there cannot be more than two adjacent woods with  *
*  the same color. Please find out how many possible ways to paint the wood.      *
*                                                                                 *
*  W W B B W  --> valid                                                           *
*  W W W      --> invalid                                                         *
***********************************************************************************/

/*------------ Solution 1: My own solution, NOT AS GOOD AS the one taught in class ------

Base Case: paint 1 or 2 pieces of woods only
white[0] = 1, black[0] = 1  --> in total 2 configurations: W, B
white[1] = 2, black[1] = 2  --> in total 4 configurations: WW, BW, BB, WB

Induction Rule: 
white[i] - represents the number of valid configurations given that the i-th wood
           is painted with WHITE color
black[i] - represents the number of valid configurations given that the i-th wood
           is painted with BLACK color

white[i] = black[i - 1] + black[i - 2]
black[i] = white[i - 1] + white[i - 2]

Explanation: 
consider i-th wood painted with White. There are two possible scenarios.
case 1 - (i - 1)-th wood painted with Black, no problem
case 2 - (i - 1)-th wood painted with White, then (i - 2)-th wood must painted with Black
The same case for i-th wood painted with Black.

time complexity: O(N)
space complexity: O(N)
*/

int paintWays_TwoColors_Sol1(int n){
	if (n <= 0)
		return 0;
	if (n == 1)
		return 2;
	if (n == 2)
		return 4;
		
	vector<int> white(n, 0);
	vector<int> black(n, 0);
	
	white[0] = 1; white[1] = 2;
	black[0] = 1; black[1] = 2;
	
	for (int i = 2; i < n; i++){
		white[i] = black[i - 1] + black[i - 2];
		black[i] = white[i - 1] + white[i - 2];
	}
	return white[n - 1] + black[n - 1];
}

/*
This solution is OK for 2 colors. However, it scales very badly. If the requirements keep the same 
but we have k colors, then this solution has high time and space complexity.

Base Case: paint 1 or 2 pieces of woods only
colors[i][0] = 1
colors[i][1] = k

Induction Rule:
colors[i][j] - represents the number of valid configurations given that the j-th wood
               is painted with i-th color
colors[i][j] = sum(colors[c][j - 1] + colors[c][j - 2]) where c != i

Explanation: 
consider j-th wood painted with i-th color. There are two possible scenarios.
case 1 - (j - 1)-th wood painted with a different color c, no problem.
case 2 - (j - 1)-th wood painted with the same i-th color, then (j - 2)-th wood must be
         painted with a different color other than i-th color.
         
time complexity O(N * k^2) 
space complexity O(N * k)  --> not efficient for k colors
*/
int paintWays_kColors_Sol1(int n, int k) {
    if (n <= 0 || k <= 0)
        return 0;
    if (n == 1)
        return k;
    if (n == 2)
        return k * k;
    
    vector<vector<int>> colors(k, vector<int>(n, 0));
    for (int j = 0; j < k; j++){
        colors[j][0] = 1;
        colors[j][1] = k;
    }
    for (int j = 2; j < n; j++){
        for (int i = 0; i < k; i++){
            for (int diffC = 0; diffC < k; diffC++){
                if (diffC != i)
                    colors[i][j] += (colors[diffC][j - 1] + colors[diffC][j - 2]);
            }
        }
    }
    
    int numWays = 0;
    for (int j = 0; j < k; j++)
        numWays += colors[j][n - 1];
    return numWays;
}



/*-------------- Solution 2: taught in class, a better solution --------------------

Base Case: paint 1 piece of wood only
same[0] = 0 
diff[0] = 2

Induction Rule: 
same[i] - represents total number of valid configurations given that the i-th wood has the 
          same color as (i - 1)-th wood
diff[i] - represents total number of valid configurations given that the i-th wood has different
          colors as (i - 1)-th wood

same[i] = diff[i - 1]
diff[i] = same[i - 1] + diff[i - 1]

Explanation:
For i-th wood, it has two scenarios
case 1: the i-th wood has the same color as the (i - 1)-th wood, then the (i - 1)-th wood must have a different 
        color with (i - 2)-th
case 2: the i-th wood has a different color than the (i - 1)-th wood, then whether (i - 1)-th wood has the same
        or different colors with (i - 2)-th does not matter

time complexity: O(N)
space complexity: O(N)
*/
int paintWays_TwoColors_Sol2(int n){
	if (n <= 0)
		return 0;
	if (n == 1)
		return 2;
		
	vector<int> same(n, 0);
	vector<int> diff(n, 0);
	
	same[0] = 0; diff[0] = 2;
	
	for (int i = 1; i < n; i++){
		same[i] = diff[i - 1];
		diff[i] = same[i - 1] + diff[i - 1];
	}
	
	return same[n - 1] + diff[n - 1];
}


/*
This solution is very easy to scale. If the requirements keep the same but we have
k colors, there are only SLIGHT changes to the solution.

Base Case: paint 1 piece of wood only
same[0] = 0
diff[0] = k

Induction Rule: 
same[i] - represents total number of valid configurations given that the i-th wood has the 
          same color as (i - 1)-th wood
diff[i] - represents total number of valid configurations given that the i-th wood has different
          colors as (i - 1)-th wood

same[i] = diff[i - 1]
diff[i] = (same[i - 1] + diff[i - 1]) * (k - 1)

Explanation:
For the i-th wood, when it has a different color than the (i - 1)-th wood, then whether (i - 1)-th wood 
has the same or different colors with (i - 2)-th does not matter. The only thing is we need to ensure
i-th wood has a different color as (i - 1)-th wood and there are (k - 1) choices.

time complexity: O(N)
space complexity: O(N) --> efficient for k colors
*/
int paintWays_kColors_Sol2(int n, int k){
	if (n <= 0)
		return 0;
	if (n == 1)
		return k;
		
	vector<int> same(n, 0);
	vector<int> diff(n, 0);
	
	same[0] = 0; diff[0] = k;
	
	for (int i = 1; i < n; i++){
		same[i] = diff[i - 1];
		diff[i] = (same[i - 1] + diff[i - 1]) * (k - 1); 
	}
	
	return same[n - 1] + diff[n - 1];
}

/*
Further optimize space complexity. Only care about same[i - 1] and diff[i - 1].

time complexity: O(N)
space complexity: O(1)
*/
int paintWays_kColors_Sol2_Space(int n, int k){
	if (n <= 0)
		return 0;
	if (n == 1)
		return k;
		
	int same = 0, diff = k;
	
	for (int i = 1; i < n; i++){
		int prevSame = same;
		same = diff;
		diff = (prevSame + diff) * (k - 1); 
	}
	
	return same + diff;
}

/*
Summary: 
1. Proper abstraction is very important. (specific White/Black colors Vs. abstract Same/Diff)
2. Physical meaning is very important.
*/

int main(){
	int n = 15, k = 6;
	//int n = 15, k = 2;
	//int n = 2, k = 10;
	
	cout << "solution 1" << endl;
	cout << paintWays_TwoColors_Sol1(n) << endl;
	cout << paintWays_kColors_Sol1(n, k) << endl;	
	cout << endl;
	
	cout << "solution 2" << endl;
	cout << paintWays_TwoColors_Sol2(n) << endl;
	cout << paintWays_kColors_Sol2(n, k) << endl;
	cout << paintWays_kColors_Sol2_Space(n, k) << endl;
	
	return 0;
}
