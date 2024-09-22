_[homepage](../../index.md)_

>[!definition] 贪心的本质是选择每一阶段的局部最优，从而达到全局最优
>**贪心没有套路，说白了就是常识性推导加上举反例**

![[8_Greedy-20240921174701224.webp]]
## 贪心一般解题步骤

1. 将问题分成若干子问题
2. 找出适合的贪心策略
3. 求每一个子问题的最优解
4. 将局部最优解堆叠成全局最优解
![[8_Greedy-20240921180459444.webp]]


### 455 Assign Cookies

Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.

Each child `i` has a greed factor `g[i]`, which is the minimum size of a cookie that the child will be content with; and each cookie `j` has a size `s[j]`. If `s[j] >= g[i]`, we can assign the cookie `j` to the child `i`, and the child `i` will be content. Your goal is to maximize the number of your content children and output the maximum number.

>[!attention] for 循环遍历胃口
>- 遍历胃口，满足不了就move on，看下一个孩子能不能被当前最大的饼干满足
>- 如果遍历饼干，满足不了当前胃口最大的孩子，还move on饼干？那更不可能有小饼干满足了

```cpp
int findContentChildren(vector<int>& g, vector<int>& s) {
	sort(g.begin(), g.end()); // 胃口
	sort(s.begin(), s.end()); // 饼干
	int children = 0;
	int j = s.size() - 1; // 饼干

	for(int i = g.size() - 1; i >= 0; --i) 
	{
		if(j >= 0 && s[j] >= g[i])
		{
			--j;
			++children;
		}
	}
	return children;
}
```

### 376 Wiggle Subsequences

A **wiggle sequence** is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.

- For example, `[1, 7, 4, 9, 2, 5]` is a **wiggle sequence** because the differences `(6, -3, 5, -7, 3)` alternate between positive and negative.
- In contrast, `[1, 4, 7, 2, 5]` and `[1, 7, 4, 5, 5]` are not wiggle sequences. The first is not because its first two differences are positive, and the second is not because its last difference is zero.

A **subsequence** is obtained by deleting some elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.

Given an integer array `nums`, return _the length of the longest **wiggle subsequence** of_ `nums`.

>[!tip] 3 situations
> 1. local maximum or minimum, sign(pre) != sign(cur)
> 2. plane
> 	1. 平台是极值, 取最后一个 (pre >= 0 && cur < 0) || (pre <= 0 && cur > 0)
> 	2. **单调中间有平台 pre 只有在找到极值时才更新，这样pre才能保证表示的是前面的趋势，用来做判断**
> 3. 首尾：默认有一个, 初始化pre = 0

```cpp
int wiggleMaxLength(vector<int>& nums) {
	int preDiff = 0, nextDiff = 0;
	int count = 1;
	for(int i = 0; i < nums.size() - 1; ++i)
	{
		nextDiff = nums[i + 1] - nums[i];
		if((preDiff <= 0 && nextDiff > 0) || (preDiff >= 0 && nextDiff < 0))
		{
			preDiff = nextDiff;
			++count;
		}
	}
	return count;
}
```

### 53 Maximum Subarray
Given an integer array `nums`, find the subarray with the largest sum, and return _its sum_.

>[!tip] 每次sum为负值时，就抛弃已有的sum重置为0，重新计算新的sum

```cpp
int maxSubArray(vector<int>& nums) {
	int max = INT_MIN;
	int count = 0;
	for(int& i : nums)
	{
		count += i;
		if(count > max) // max 不一定大于零，但只要发现更大的就会一直更像
		{
			max = count;
		}

		if(count < 0) // 只要小于0，必然会拖累下一个数
		{
			count = 0;
		}
	}
	return max;
}
```

### 122 买卖股票的最佳时间 II

只要收集所有正利润的天数就好了
```cpp
for (int i = 1; i < prices.size(); i++) {
	result += max(prices[i] - prices[i - 1], 0);
}
```

### 55 跳跃游戏
给定一个非负数组，表示每个下标可跳跃的步长，求*能否*跳跃到终点

题解：
从起点开始，计算能到达的最远处`cover`, 在`cover`范围内，计算每个位置能到的最远处，更新`cover`
```cpp
int cover = 0;
for(int i = 0; i <= cover; ++i)
{
	cover = max(i + nums[i], cover);
	if(cover >= nums.size() - 1)
		return true;
}
return false;
```

### 45 跳跃游戏 II
使用*最少的跳跃次数*到达数组的最后一个位置

题解：
1. 在*这一步覆盖* `curCover` 范围内，遍历每个位置，获得下一步的最大覆盖`nextCover`. 因为只要你能够获得更大的覆盖，其实意味着就是要多走一步才能得到的更新。
2. 当到达这一步的最大覆盖 `i == curCover`:
   查看`nextCover >= nums.size()`, 决定是继续更新还是`return`

```cpp
int jump(vector<int>& nums) {
	if (nums.size() == 1) return 0;
	int steps = 0;
	int curCover = 0, nextCover = 0;
	for(int i = 0; i <= curCover; ++i)
	{
		nextCover = max(i + nums[i], nextCover);
		if(i == curCover)
		{
			++steps;
			curCover = nextCover;
			if(curCover >= nums.size() - 1)
				break;
		}
	}
	return steps;
}
```

### 1005 K次取反后最大化的数组和

题解：
1. 按照绝对值从大到小排序
   
   ```cpp
   static bool cmp(int a, int b)
   {
       return abs(a) > abs(b);
   }
   
   int largestSumAfterKNegations(vector<int>& A, int K) {
	   sort(A.begin(), A.end(), cmp);
	   // ...
   }
	```

2. 正序遍历数组，遇到负数，如果还有次数就反转
3. 如果反转完所有负数，还有剩余次数，对一个数反转两次就还是原值，所以直接取除以2的余数，如果是奇数，就反转数组最后一个数
4. 返回数组值和



### 134 加油站
第 `i` 个加油站有汽油 `gas[i]`升。从第`i`i 个加油站开往第` i+1` 个加油站需要消耗汽油 `cost[i]` 升.
如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。

题解：
每个加油站的剩余量`rest[i] = gas[i] - cost[i]`.
1. i从0开始累加`rest[i]`，和记为 `curSum`
2. 一旦小于零，说明 [0, i] 区间都不能作为起始位置，因为这个区间选择任何一个位置作为起点，**到i这里都会断油**，那么起始位置从i+1算起，再从0计算curSum。
3. 同时如果`rest`数组的和小于0，那么无论如何都走不完一圈

```cpp
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
	int curSum = 0;
	int totalSum = 0;
	int start = 0;
	for (int i = 0; i < gas.size(); i++) {
		
		curSum += gas[i] - cost[i]; // 加上最新的rest[i]
		totalSum += gas[i] - cost[i]; // 计算总rest
		
		if (curSum < 0) {   // 当前累加rest[i]和 curSum一旦小于0，第二步
			start = i + 1;  // 起始位置更新为i+1
			curSum = 0;     // curSum从0开始
		}
	}
	// 说明怎么走都不可能跑一圈了，第三步
	if (totalSum < 0) return -1; 
	return start;
}
```

### 135 分发糖果
- 每个孩子至少分配到 1 个糖果。
- 相邻的孩子中，评分高的孩子必须获得更多的糖果。
  
题解：
**两次贪心**的策略：

- 一次是*从左到右*遍历，只比较*右边孩子评分比左边大*的情况。正序遍历是因为右边的值依赖左边的值
  `if(nums[i] > nums[i - 1]) candy[i] = candy[i - 1] + 1 
- 一次是从右到左遍历，只比较左边孩子评分比右边大的情况。**倒叙遍历是因为左边的值依赖右边的值**
  `if(nums[i] > nums[i + 1]) candy[i] = candy[i + 1] + 1 

### 860 柠檬水找零

- 情况一：账单是5，直接收下。
- 情况二：账单是10，消耗一个5，增加一个10
- 情况三：账单是20，优先消耗一个10和一个5，如果不够，再消耗三个5
  **因为美元10只能给账单20找零，而美元5可以给账单10和账单20找零，美元5更万能！**

### ⭐406 根据身高重建队列
每个 `people[i] = [hi, ki]` 表示第 `i` 个人的身高为 `hi` ，*前面 正好 有 `ki` 个身高`>=hi` 的人*

>[!important] 本题有两个维度，h和k，看到这种题目一定要想如何确定一个维度
>>[!tip] 每一个人前面的身高一定是大于等于自己的！所以先考虑`h`身高

题解：
1. 主要按身高从高到低排序，次要按照`ki` 排序
   ```cpp
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
	```

2. 优先按身高高的people的k来插入
	```cpp
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		sort (people.begin(), people.end(), cmp);
		list<vector<int>> que; // list底层是链表实现，插入效率比vector高的多
		for (int i = 0; i < people.size(); i++) {
			int position = people[i][1]; // 插入到下标为position的位置
			std::list<vector<int>>::iterator it = que.begin();
			while (position--) { // 寻找在插入位置
				it++;
			}
			que.insert(it, people[i]);
		}
		return vector<vector<int>>(que.begin(), que.end());
	}
	```


### 452 用最少数量的箭引爆气球
在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 `xstart，xend`， 且满足  `xstart ≤ x ≤ xend`，则该气球会被引爆。可以射出的弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前进。我们想找到使得所有气球全部被引爆，所需的弓箭的最小数量。

>[!tip] 为了让气球尽可能的重叠，需要对数组进行排序。

题解：
1. 按照气球区间的起点排序，从前向后遍历
2. **如果气球重叠，在 重叠气球中 右边界的的最小值之前 一定要一个弓箭**
```cpp
 int result = 1; // points 不为空至少需要一支箭
for (int i = 1; i < points.size(); i++) {
	// 气球i和气球i-1不挨着，注意这里不是>=
	if (points[i][0] > points[i - 1][1]) {  
		result++; // 需要一支箭
	}
	else {  // 气球i和气球i-1挨着
		// 更新重叠气球最小右边界
		points[i][1] = min(points[i - 1][1], points[i][1]); 
	}
}
return result;
```

### ⭐435 无重叠区间

1. 按照右边界排序
2. 从左向右**记录非交叉区间的个数**
3. 区间*总数减去非交叉区间的个数*就是需要移除的区间个数了

```cpp
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
	if (intervals.size() == 0) return 0;
	sort(intervals.begin(), intervals.end(), cmp);
	int count = 1; // 记录非交叉区间的个数
	int end = intervals[0][1]; // 记录区间分割点
	for (int i = 1; i < intervals.size(); i++) {
		if (end <= intervals[i][0]) { // 非交叉
			end = intervals[i][1];
			count++;
		}
	}
	return intervals.size() - count;
}
```

### 763 划分字母区间
字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。返回一个表示每个字符串片段的长度的列表。
```
- 输入：S = "ababcbacadefegdehijhklij"
- 输出：[9,7,8] 解释： 划分结果为 "ababcbaca", "defegde", "hijhklij"。
```

题解：
1. 统计每个字母最后出现的位置
	```cpp
	int hash[27] = {0}; // i为字符，hash[i]为字符出现的最后位置
	for (int i = 0; i < S.size(); i++) { // 统计每一个字符最后出现的位置
		hash[S[i] - 'a'] = i;
	}
	```

2. 从前到后遍历，更新右边界为当前区间内所有字符的最远边界


### 56 合并区间
合并重叠区间

```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
	vector<vector<int>> result;
	if (intervals.size() == 0) return result; // 区间集合为空直接返回
	
	// 排序的参数使用了lambda表达式
	sort(intervals.begin(), intervals.end(), 
		[](const vector<int>& a, const vector<int>& b){return a[0] < b[0];});

	// 第一个区间就可以放进结果集里，后面如果重叠，在result上直接合并
	result.push_back(intervals[0]); 

	for (int i = 1; i < intervals.size(); i++) {
		if (result.back()[1] >= intervals[i][0]) { // 发现重叠区间
			// 合并区间，只更新右边界就好，因为result.back()的左边界一定是最小值，因为我们按照左边界排序的
			result.back()[1] = max(result.back()[1], intervals[i][1]); 
		} else {
			result.push_back(intervals[i]); // 区间不重叠 
		}
	}
	return result;
}
```

### 78 单调递增的数字
和分糖果一个思路，这个题只用从后向前遍历。

题解：
- 如果前一位比后一位笑，要保证数字小于N，是不可能让后一位+1的，只可能是让后一位变成9，前一位再 -1

```cpp
int monotoneIncreasingDigits(int N) {
	string strNum = to_string(N);
	// flag用来标记赋值9从哪里开始
	// 设置为这个默认值，为了防止第二个for循环在flag没有被赋值的情况下执行
	int flag = strNum.size();
	for (int i = strNum.size() - 1; i > 0; i--) {
		if (strNum[i - 1] > strNum[i] ) {
			flag = i;
			strNum[i - 1]--;
		}
	}
	for (int i = flag; i < strNum.size(); i++) {
		strNum[i] = '9'; // 9999 
	}
	return stoi(strNum);
}
```

>[!info]
>`string s = to_string(i)`
>`int i = stoi(s);`

### 96 监控二叉树
给定一个二叉树，我们在树的节点上安装摄像头。节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。
计算监控树的所有节点所需的最小摄像头数量。

>[!important] 头结点放不放摄像头也就省下一个摄像头， 叶子节点放不放摄像头省下了的摄像头数量是指数阶别的。

使用后序遍历也就是左右中的顺序
- 0：该节点无覆盖
- 1：本节点有摄像头
- 2：本节点有覆盖
* 空节点就属于有覆盖 无摄像头

```cpp
int result = 0;
int traversal(TreeNode* cur) {

    // 空节点，该节点有覆盖
    if (!cur) return 2;

    int left = traversal(cur->left);    // 左
    int right = traversal(cur->right);  // 右

    // 逻辑处理                            // 中
    
    // 任何一个子节点无覆盖，都需要加摄像头
    if(left == 0 || right == 0) 
    {
	    ++result;
	    return 1;
    }

	// 任何一个子节点有摄像头，本节点都属被覆盖
	if(left == 1 || right == 1)
	{
		return 2;
	}

	// 两个子节点都被覆盖，那本节点要空下来，等父节点摄像头
    return 0;
}
```