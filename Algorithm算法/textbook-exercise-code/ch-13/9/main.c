#include <stdio.h>
#include <string.h>
char* intput = "caba";
char* output;
int outputLength;


int dp[1000][1000];

#define DP(i, j) (((j) - (i) > 0) ? dp[i][j] : 0)


char* solve(char* s) {
	char* ans = NULL;
	int ansLength = 0;
	int n = strlen(s);
	for(int i = n - 1; i >= 0; i -= 1) {
		for(int j = i + 1; j < n; j += 1) {
			dp[i][j] = DP(i + 1, j - 1) + (s[i] == s[j]);
			if(dp[i][j] > ansLength) {
				ansLength = dp[i][j];
				ans = s + i;
			}
		}
	}
	outputLength = ansLength;
	return ans;
}


int main() {
	output = solve(intput);

	for(int i = 0; i < outputLength; i += 1) {
		putchar(output[i]);
	}
	putchar('\n');
	return 0;
}
