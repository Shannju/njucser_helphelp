#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 2500 + 5

int dp[MAX_N][MAX_N];

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int lengthOfLIS(int* nums, int numsSize){
	for(int i = 0; i < MAX_N; i += 1) {
		for(int j = 0; j < MAX_N; j += 1) {
			dp[i][j] = INT32_MAX;
		}
	}
	dp[0][1] = nums[0];
	for(int i = 1; i < numsSize; i += 1) {
		int tail = nums[i];
		dp[i][1] = MIN(tail, dp[i - 1][1]);
		for(int j = 1; j <= i; j += 1) {
			if(dp[i - 1][j] == INT32_MAX) {
				break;
			}
			if(tail > dp[i - 1][j]) {
				dp[i][j + 1] = MIN(tail, dp[i - 1][j + 1]);
			}	
			else dp[i][j + 1] = dp[i - 1][j + 1];
		}	
	}
	int ans = 0;
	for(int i = MAX_N; i >= 0; i -= 1) {
		if(dp[numsSize - 1][i] != INT32_MAX) {
			ans = i;
			break;
		}
	}
	return ans;
}

int main() {
  int numsSize;
  scanf("%d", &numsSize);
  int* nums = (int*)malloc(sizeof(int) * numsSize);
 	for(int i = 0; i < numsSize; i += 1) {
		scanf("%d", nums + i);
	}	
	int ans = lengthOfLIS(nums, numsSize);
	return 0;
}
