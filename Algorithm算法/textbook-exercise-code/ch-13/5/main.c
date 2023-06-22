#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int dp[100][100];

int* S;
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))


int minCost(int k, int* a, int n) {
	S = (int*)malloc(sizeof(int) * n);

	S[0] = a[0];
	for(int i = 0; i < n; i += 1) {
		S[i] = S[i - 1] + a[i];
	}

	for(int i = 0; i < n; i += 1) {
		for(int j = 1; j <= k; j += 1) {
			if(i == 0) dp[i][j] = a[0];
			else if(j == 1) dp[i][j] = S[i];
			else dp[i][j] = INT32_MAX;
		}
	}

	for(int i = 1; i < n; i += 1) {
		for(int j = 2; j <= k; j += 1) {
			for(int l = 0; l < i; l += 1) {
				int tail = S[i] - S[l];
				dp[i][j] = MIN(MAX(dp[l][j - 1], tail), dp[i][j]);
			}
		}	
	}
	return dp[n - 1][k];
}

int main() {
	int k;
	int size;
	scanf("%d %d", &k, &size);
	int* a = (int*)malloc(sizeof(int) * size);
	for(int i = 0; i < size; i += 1) {
		scanf("%d", a + i);
	}
	int ans = minCost(k, a, size);
	return 0;
}



