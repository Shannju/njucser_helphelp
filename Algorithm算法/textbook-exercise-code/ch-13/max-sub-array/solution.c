#define MAX(x, y) ((x) > (y) ? (x) : (y))

int maxSubArray(int* nums, int numsSize){
    int dp[numsSize];
    dp[0] = nums[0];
    int temp = nums[0];
    for(int i = 1; i < numsSize; i += 1) {
        temp = MAX(nums[i], temp + nums[i]);
        dp[i] = MAX(temp, dp[i - 1]);
    }
    return dp[numsSize - 1];
}
