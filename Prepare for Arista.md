- Reviewed C++ STL, Template, Smart ptr

### Algo
#### Dynamic programming:
1. leetcode 300 [Longest Increasing Subsequence](https://leetcode.cn/problems/longest-increasing-subsequence/)
	```cpp
	for (int i = 1; i < nums.size(); i++) {
	    for (int j = 0; j < i; j++) {
	        if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
	    }
	    if (dp[i] > result) result = dp[i]; // 取长的子序列
	}
	```
2. [746. Min Cost Climbing Stairs](https://leetcode.cn/problems/min-cost-climbing-stairs/description/)
>[!infp] the top of the stairs is at cost.size() + 1
```cpp
int minCostClimbingStairs(vector<int>& cost) {
	vector<int> dp(cost.size() + 1, 0); // the top of the stairs is at cost.size() + 1
	for(int i = 2; i <= cost.size(); ++i)
	{
		dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
	}
	return dp.back();
}
```

01 Backpack
```cpp
dp[i][j] = max(dp[i - 1][j], d[i - 1][j - weight[j]] + value[i]);
```
Full Backpack
```cpp
dp[i][j] = max(dp[i - 1][j], d[i][j - weight[i]] + value[i]);
```