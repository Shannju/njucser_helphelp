// leetcode 152
#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : y)
#define MIN(x, y) ((x) < (y) ? (x) : y)
#define MAX3(x, y, z) MAX(MAX(x, y), z)
#define MIN3(x, y, z) MIN(MIN(x, y), z)

int maxProduct(int* nums, int numsSize){
	int* max = (int*)malloc(numsSize * sizeof(int));
	int* min = (int*)malloc(numsSize * sizeof(int));
	int ans = nums[0];
	max[0] = min[0] = nums[0];
	for(int i = 1; i < numsSize; i += 1) {
		if(nums[i] >= 0) {
			max[i] = MAX(max[i - 1] * nums[i], nums[i]);
			min[i] = MIN(min[i - 1] * nums[i], nums[i]);
		}
		else {
			max[i] = MAX(min[i - 1] * nums[i], nums[i]);
			min[i] = MIN(max[i - 1] * nums[i], nums[i]);
		}
		ans = MAX(ans, max[i]);
	}
	return ans;
}

int main() {
	int n;
	scanf("%d", &n);
	int *a = (int*)malloc(sizeof(int) * n);
	for(int i = 0; i < n; i += 1) {
		scanf("%d", a + i);
	}
	int ans = maxProduct(a, n);
	return 0;
}

