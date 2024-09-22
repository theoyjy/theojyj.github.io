_[homepage](../../index.md)_

### 解题方法
1. 想清楚 `dp` 数组以及**下标** 的含义
2. 递推公式
3. `dp` 数组如何初始化
4. 确定遍历顺序
5. 打印dp数组
	1. 判断数组写错了
	2. 还是递推公式错了

## 基础
### 509 斐波那契数
1. `dp[i]` 就是第i个斐波那契数
2. `dp[i] = dp[i-1] + dp[i-2]`
3. `dp[0] = 0, dp[1] = 1`
4. 后依赖前，所以是从前往后遍历
5. 打印验证

```cpp
int fib(int N) {
	if (N <= 1) return N;
	vector<int> dp(N + 1);
	dp[0] = 0;
	dp[1] = 1;
	for (int i = 2; i <= N; i++) {
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	return dp[N];
}
```

### 70 爬楼梯
1. `dp[i]` 表示到第i层的有多少种方法
2. **是之和** `dp[i] = dp[i - 1] + dp[i - 2]`
3. `dp[0] = 0, dp[1] = 1`
4. 从前向后
5. 0 1 2 3 5 8

*本质就是斐波那契*

### 746 使用最小花费爬楼梯
给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。

==你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。==

1. `dp[i]` 表示到第i层的最小花费
2. **是之和** `dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2])`
3. ==**你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯**:==  
   ==`dp[0] = 0, dp[1] = 0`==
4. 从前向后
5. ...

### 62 不同路径

1. `dp[i][j]` 表示到达 [i, j] 的总路径
2. `dp[i][j] = dp[i-1][j] + dp[i][j-1]`
3.  ⭐
```cpp
for (int i = 0; i < m; i++) dp[i][0] = 1;
for (int j = 0; j < n; j++) dp[0][j] = 1;
```

4. ==左上[1, 1]到右下[m - 1, n - 1]==

```cpp
int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) dp[i][0] = 1;
        for (int j = 0; j < n; j++) dp[0][j] = 1;
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
```

### 63 不同路径 II
有障碍物

初始化的代码需要改变
![[9_Dynamic_Programming-20240922173041444.webp|400]]
```cpp
vector<vector<int>> dp(m, vector<int>(n, 0));
for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;
```


```cpp
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	if (obstacleGrid[m - 1][n - 1] == 1 || obstacleGrid[0][0] == 1) //如果在起点或终点出现了障碍，直接返回0
		return 0;
	vector<vector<int>> dp(m, vector<int>(n, 0));
	for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
	for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			if (obstacleGrid[i][j] == 1) continue;
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[m - 1][n - 1];
}
```

### 343 整数拆分
给定一个正整数 n，将其拆分为**至少**两个正整数的和，并使这些整数的**乘积最大化**

1. `dp[i]` 分拆数字i，可以得到的最大乘积为dp[i]
2. 那么从1遍历j，比较`(i - j) * j`和`dp[i - j] * j `取最大的。递推公式：
	`dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));`
	- `j * dp[i - j]`是==拆分成两个以及两个以上==的个数相乘。
	- 如果定义`dp[i - j] * dp[j]` 也是默认将一个数==强制拆成4份以及4份==以上了。
3. `dp[0] = 0, dp[1] = 0, dp[2] = 1`
4. 从前向后

```cpp
int integerBreak(int n) {
	vector<int> dp(n + 1);
	dp[2] = 1;
	for (int i = 3; i <= n ; i++) {
		for (int j = 1; j <= i / 2; j++) {
			dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
		}
	}
	return dp[n];
}
```

### 96 不同的二叉搜索树
![[9_Dynamic_Programming-20240922174829864.webp|500]]

==`dp[3]`，就是 元素1为头结点搜索树的数量 + 元素2为头结点搜索树的数量 + 元素3为头结点搜索树的数量==

```text
元素1为头结点搜索树的数量 = 右子树有2个元素的搜索树数量 * 左子树有0个元素的搜索树数量
						= dp[2] * dp[0] 

元素2为头结点搜索树的数量 = 右子树有1个元素的搜索树数量 * 左子树有1个元素的搜索树数量
						= dp[1] * dp[1] 

元素3为头结点搜索树的数量 = 右子树有0个元素的搜索树数量 * 左子树有2个元素的搜索树数量
						= dp[0] * dp[2] 

=>
所以dp[3] = dp[2] * dp[0] + dp[1] * dp[1] + dp[0] * dp[2]
```

1. **dp[i] ： 1到i为节点组成的二叉搜索树的个数为dp[i]**。
2. `j` 表示以元素j为头节点， 所以`1 <= j <= i`
```cpp
for(int j = 1; j < i; ++j) 
{
	dp[i] += dp[j - 1] * dp[i - j];
}
```
3. `dp[0] = 1` 空树也是树

```cpp
int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= i; ++j)
                dp[i] += dp[j - 1] * dp[i - j];
    
        return dp[n];
    }
```

## 背包问题

>[!tip] 掌握01背包和完全背包，就够用了，最多可以再来一个多重背包

![[9_Dynamic_Programming-20240922181030263.webp]]

![[9_Dynamic_Programming-20240922181323142.webp|400]]

### Step1 二维数组`dp[i][j]` 分别表示：物品 和 背包容量
* i 来表示物品、j表示背包容量。

### Step 2 动态转移方程
两种情况：
- **不放物品i**：背包容量为j，里面不放物品i的最大价值是`dp[i - 1][j]`。
- **放物品i**：背包空出物品i的容量后，
	- 背包容量为`j - weight[i]`
	- `dp[i - 1][j - weight[i]]` 为背包容量为`j - weight[i]`且不放物品i的最大价值
	- 那么`dp[i - 1][j - weight[i]] + value[i] `（物品i的价值），就是背包放物品i得到的最大价值

递归公式： `dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);`

### Step 3 初始化
1. 重量为0时，`dp[0][j]` 全都是0
2. 只选第一个物品时，直到重量大于等于第1个物品，价值才从0变成`value[0]`
```cpp
// 初始化 dp
vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));
for (int j = weight[0]; j <= bagweight; j++) {
    dp[0][j] = value[0];
}
```

### Step 4 遍历顺序

>[!important] 先遍历物品更好理解

```cpp
int n, bagweight;// bagweight代表行李箱空间

cin >> n >> bagweight;

vector<int> weight(n, 0); // 存储每件物品所占空间
vector<int> value(n, 0);  // 存储每件物品价值

for(int i = 0; i < n; ++i) {
	cin >> weight[i];
}
for(int j = 0; j < n; ++j) {
	cin >> value[j];
}
// dp数组, dp[i][j]代表行李箱空间为j的情况下,从下标为[0, i]的物品里面任意取,能达到的最大价值
vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

// 初始化, 因为需要用到dp[i - 1]的值
// j < weight[0]已在上方被初始化为0
// j >= weight[0]的值就初始化为value[0]
for (int j = weight[0]; j <= bagweight; j++) {
	dp[0][j] = value[0];
}

for(int i = 1; i < weight.size(); i++) { // 遍历科研物品
	for(int j = 0; j <= bagweight; j++) { // 遍历行李箱容量
		if (j < weight[i]) // 如果装不下这个物品,那么就继承dp[i - 1][j]的值
			dp[i][j] = dp[i - 1][j]; 
		else {
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
		}
	}
}
cout << dp[n - 1][bagweight] << endl;
```

### 一维滚动数组优化

>[!important]  
>1. 每一行都从装的下当前物品的重量开始遍历
>2. 倒着遍历，因为后面依赖上一行前面的值，所以后面的覆盖不影响前面，前面的覆盖就会影响后面

```cpp
// 创建一个动态规划数组dp，初始值为0
vector<int> dp(N + 1, 0);

// 外层循环遍历每个类型的研究材料
for (int i = 0; i < M; ++i) {
	// 内层循环从 N 空间逐渐减少到当前研究材料所占空间
	for (int j = N; j >= costs[i]; --j) {
		// 考虑当前研究材料选择和不选择的情况，选择最大值
		dp[j] = max(dp[j], dp[j - costs[i]] + values[i]);
	}
}
```


### 416 分割等和子集
是否可以将这个数组分割成两个子集，使得两个子集的元素和相等

>[!important] 
>- 其实就是要找，是否有一个子集的和是`sum/2`
>- 每个元素只能用一次 -> 01背包问题

>[!tip]
>- 背包的体积为sum / 2
>- 背包要放入的商品（集合里的元素）==重量为 元素的数值，价值也为元素的数值==
>- ==背包如果正好装满，说明找到了总和为 sum / 2 的子集。==
>- 背包中每一个元素是不可重复放入。

1. `dp[j]`表示 背包总容量（所能装的总重量）是`j`，放进物品后，背的最大重量为`dp[j]`
2. `dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);`
3. `dp[0] = 0`

```cpp
bool canPartition(vector<int>& nums) {
	int sum = 0;
	for(int & i : nums)
	{
		sum += i;
	}
	if(sum % 2)
		return false;
	
	sum /= 2;
	vector<int> dp(sum + 1, 0);

	for(int i = 0; i < nums.size(); ++i)
	{
		for(int j = sum; j >= nums[i]; j--)
		{
			dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
		}
	}

	return dp[sum] == sum;
}
```


## 完全背包


## 打家劫舍
### 198 打家劫舍
不能偷相邻两家的

>[!caution] 
>1. 重点是遍历完数组，所以从`dp[0]` 对应的就是` nums[0]`
>   返回的也是`nums`对应的最后一个而已
>2. 初始化注意`dp[1] = max(nums[0], nums[1]);

```cpp
int rob(vector<int>& nums) {
	if(nums.size() == 0)
		return 0;
	if(nums.size() == 1)
		return nums[0];

	vector<int> dp(nums.size(), 0);
	dp[0] = nums[0];
	dp[1] = max(nums[0], nums[1]);
	for(int i = 2; i < nums.size(); ++i)
		dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
	return dp.back();
}
```

### 213.打家劫舍II
*首位相连了*

>[!important] 
>对于一个数组，成环的话, 为了避免首位同时被偷，会产生如下三种选择结构：
>1. 首位都不选
>2. 只选首，不选尾
>3. 只选尾，不选首
>其中2，3都包含1，所以只需要把2，3当作上一题一样各跑一遍，取最大值就好了
>


```cpp
int rob(vector<int>& nums) {
	if (nums.size() == 0) return 0;
	if (nums.size() == 1) return nums[0];
	int result1 = robRange(nums, 0, nums.size() - 2); // 情况二
	int result2 = robRange(nums, 1, nums.size() - 1); // 情况三
	return max(result1, result2);
}
// 198.打家劫舍的逻辑
int robRange(vector<int>& nums, int start, int end) {
	if (end == start) return nums[start];
	vector<int> dp(nums.size());
	dp[start] = nums[start];
	dp[start + 1] = max(nums[start], nums[start + 1]);
	for (int i = start + 2; i <= end; i++) {
		dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
	}
	return dp[end];
}
```

### 337.打家劫舍 III
除了“根”之外，*每栋房子有且只有一个“父“房子与之相连*。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列*类似于一棵二叉树*”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。
**本题一定是要后序遍历，因为通过递归函数的返回值来做下一步计算**。

1. `dp[i][2]` 第i家，`dp[i][0]` 不偷最大值, `dp[i][2]` 偷 最大值
2. `dp[i][0] = max(left[0], left[1]) + max(right[0], right[1])`
   `dp[i][1] = left[0] + right[0] + cur->value`

```cpp
int rob(TreeNode* root) {
	vector<int> result = robTree(root);
	return max(result[0], result[1]);
}

// 长度为2的数组，0：不偷，1：偷
vector<int> robTree(TreeNode* cur) {
	if (cur == NULL) return vector<int>{0, 0};
	vector<int> left = robTree(cur->left);
	vector<int> right = robTree(cur->right);
	// 偷cur，那么就不能偷左右节点。
	int val1 = cur->val + left[0] + right[0];
	// 不偷cur，那么可以偷也可以不偷左右节点，则取较大的情况
	int val2 = max(left[0], left[1]) + max(right[0], right[1]);
	return {val2, val1};
}
```
## 股票

## 子序列

### 300 最长递增子序列

1. dp[i] 以i结尾的最长子序列长度
`if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);`

>[!info] 只从i向前找到一个比nums[i]小的值是不够的，要遍历所有比nums[i]小的值并更新才行


```cpp
int lengthOfLIS(vector<int>& nums) {
	vector<int> dp(nums.size(), 1);
	dp[0] = 1;
	int res = 1;
	for(int i = 1; i < nums.size(); ++i)
	{
		for (int j = 0; j < i; j++) // 遍历前面所有比自己小的数，获取最大长度
		{
			if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
		}
		if(dp[i] > res)
			res = dp[i];
	}
	return res;
}
```

### 1143 最长公共子序列

1. `dp[i][j]`：长度为`[0, i - 1]`的字符串`text1`与长度为`[0, j - 1]`的字符串`text2`的最长公共子序列为`dp[i][j]`
   
   >[!info]
   >如果定义 `dp[i][j]`为 以长度 `i` 的text1子字符串，和以长度`j`的字符串text2，那么 第一行和第一列毕竟要进行初始化，如果`nums1[i] == nums2[0] `相同的话，对应的 `dp[i][0] = 1`, 因为此时最长公共子序列为1。 `nums2[j] == nums1[0]`相同的话同理。
   >```cpp
   >for(int i = 0; i < text1.size(); ++i) 
   >    if(text1[i] == text2[0]) dp[i][0] = 1;
   >for(int j = 0; j < text2.size(); ++j) 
   >    if(text1[0] == text2[j]) dp[0][j] = 1;
   >```
   
2. 
```cpp
if (text1[i - 1] == text2[j - 1]) {
    dp[i][j] = dp[i - 1][j - 1] + 1;
} else {
    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
}
```


```cpp
int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
        for(int i = 1; i <= text1.size(); ++i)
        {
            for(int j = 1; j <= text2.size(); ++j)
            {
                if(text1[i - 1] == text2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp.back().back();
    }
```