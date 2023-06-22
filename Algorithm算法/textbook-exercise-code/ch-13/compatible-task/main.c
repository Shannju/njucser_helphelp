#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct Task {
	int start;
	int end;
} Task;


int compare(const void* a, const void* b) {
	Task *ta = (Task*)a, *tb = (Task*)b;
	return ta->end - tb->end;
}

static inline bool isCompatible(Task* a, Task* b) {
	return a->end <=  b->start;
}


//#define GREEDY
#ifdef GREEDY
// greedy solution
int activitySelection(int* start, int* end, int n) {
	// Your code here
	Task* task = (Task*)malloc(sizeof(Task) * n);
	for(int i = 0; i < n; i += 1) {
		task[i] = (Task){.start = start[i], .end = end[i]};
	}
	qsort(task, n, sizeof(Task), compare);

	Task* t = task;
	int ans = 1;
	for(int i = 1; i < n; i += 1) {
		if(isCompatible(t, task + i)) {
			ans += 1;
			t = task + i;
		}
	}
	return ans;
}
#endif

#define MAX_N 20000 + 5
#define MAX(x, y) ((x) > (y) ? (x) : (y))

bool isValid3(Task* task, int i, int j, int k) {
	return task[i].end < task[k].start && task[k].end < task[j].start;
}
static inline bool isValid(Task* task, int i, int j) {
	return task[i].end < task[j].start;
}
void cleanUp(int** dp, int n) {
	for(int i = 0; i < n; i += 1) {
		free(dp[i]);
	}
	free(dp);
}
/**
 * dp solution, too slow
*/
int activitySelection(int* start, int* end, int n) {
	// Your code here
	Task* task = (Task*)malloc(sizeof(Task) * n);
	for(int i = 0; i < n; i += 1) {
		task[i] = (Task){.start = start[i], .end = end[i]};
	}
	qsort(task, n, sizeof(Task), compare);
/**
 * dp[i][j] means how many tasks can be put in i.end and j.start
 */ 
	int** dp = (int**)malloc(sizeof(int*) * n);
	for(int i = 0; i < n; i += 1) {
		dp[i] = (int*)malloc(sizeof(int) * n);
		memset(dp[i], 0, sizeof(int) * n);
	}
	/**
	 * if ans == 1, means there is no any gaps in 2 task, break the recursion base
	 */ 
	int ans = 0;
	for(int i = n - 1; i >= 0; i -= 1) {
		for(int j = i + 1; j < n; j += 1) {
				if(isValid(task, i, j)) {
					for(int k = 0; k < n; k += 1) {
						if(isValid3(task, i, j, k)) {
							dp[i][j] = MAX(dp[i][j], dp[i][k] + dp[k][j] + 1);
						}
					}
					ans = MAX(dp[i][j] + 2, ans);
				}
				else {
					/**
					 * dp[i][j] should be zero 
					 */ 
					ans = MAX(dp[i][j] + 1, ans);
				}
		}

	}
	cleanUp(dp, n);
	return ans;
}



int main() {
	int n;
	scanf("%d", &n);
	int* start = (int*)malloc(sizeof(int) * 2 * n);
	int* end = start + n;
	for(int i = 0; i < n; i += 1) {
		scanf("%d", start + i);
	}
	for(int i = 0; i < n; i += 1) {
		scanf("%d", end + i);
	}
	int ans = activitySelection(start, end, n);
	return 0;
}
