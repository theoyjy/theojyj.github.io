_[homepage](../../index.md)_

**回溯法解决的问题都可以抽象为树形结构（N叉树）**

### Template

```cpp
// 1. usually return void, params depend on specific situations
void backtracking(param)
{
	// 2. Terminate condition
	if(Terminate_condition)
	{
		// save results
		// ...
		return;
	}
	
	// 3. Iteration: the size of result sets is equal to the number of children of cur node
	// 横向遍历
	for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
		处理节点;
		backtracking(路径，选择列表); // 递归
		回溯，撤销处理结果 // 总想遍历
	}
}
```

>[!success]
>递归来做层叠嵌套（可以理解是开k层for循环），**每一次的递归中嵌套一个for循环，那么递归就可以用于解决多层嵌套循环的问题了**。

### 回溯法，一般可以解决如下几种问题：

>[!important] 主要解决需要过多for循环来穷尽的可能性的问题

- 组合问题：N个数里面按一定规则找出k个数的集合
- 切割问题：一个字符串按一定规则有几种切割方式
- 子集问题：一个N个数的集合里有多少符合条件的子集
- 排列问题：N个数按一定规则全排列，有几种排列方式
- 棋盘问题：N皇后，解数独等等

## 集合

>[!tip] 每次从集合中选取元素，可选择的范围随着选择的进行而收缩，调整可选择的范围。

![[7_Backtracking-20240920204750475.webp]]

>[!important] 什么时候需要startIndex?
>如果是一个集合求组合，需要startIndex [for example](#77%20Combinations)
>如果是多个集合求组合，不需要 [for example](#17%20Letter%20Combinations%20of%20a%20Phone%20Number)

>[!info] **集合如何去重 [Question](#40%20Combination%20Sum%20II)**
>“使用过”在这个树形结构上是有两个维度的，一个维度是同一树枝上使用过，一个维度是同一树层上使用过。
>我在图中将used的变化用橘黄色标注上，可以看出在candidates[i] == candidates[i - 1]相同的情况下：
>![[7_Backtracking-20240920225734298.webp]]
>- used[i - 1] == true，说明同一树枝candidates[i - 1]使用过
>- used[i - 1] == false，说明同一树层candidates[i - 1]使用过
>  **已经到该元素的重复了，但是前面的居然没有用过，说明该元素与前一个元素的关系是同层，那么当前元素如果加入数组，起到的作用将与前面重复的一模一样，进而产生了重复**


### 77 Combinations
Given two integers `n` and `k`, return all possible combinations of `k` numbers chosen form the range `[1, n]`

>[!tip] for循环里优化剪枝
>剩余可选要能保证足够产生combination，再进行回溯
>`for (int i = startIndex; i <= n - (k - path.size()) + 1; i++)`

```cpp
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        backtracking(1, n, k);
        return res;
    }
private:
    vector<int> path;
    vector<vector<int>> res;
    
    void backtracking(int i, int n, int k)
    {
        if(path.size() == k)
        {
            res.push_back(path);
            return;
        }

        for(; i <= n - (k - path.size()) + 1; ++i) // 
        {
            path.push_back(i);
            backtracking(i + 1, n, k);
            path.pop_back();
        }
    }
};
```

### 216 Combination Sum III

Find all valid combinations of `k` numbers that sum up to `n` such that the following conditions are true:

- Only numbers `1` through `9` are used.
- Each number is used **at most once**.

Return _a list of all possible valid combinations_. The list must not contain the same combination twice, and the combinations may be returned in any order.

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        backtracking(0, 1, k, n);
        return res;
    }

private:

    void backtracking(int sum, int i, int k, int n)
    {
        if(sum == n)
        {
            if(path.size() == k)
                res.push_back(path);
            return;
        }

        for(; i <= 9 && sum + i <= n; ++i)
        {
            path.push_back(i);
            sum += i;
            backtracking(sum, i+1, k, n);
            sum -= i;
            path.pop_back();
        }
    }


private:
    vector<int> path;
    vector<vector<int>> res;
};
```


### 17 Letter Combinations of a Phone Number

Given a string containing digits from `2-9` inclusive, return all possible letter combinations that the number could represent. Return the answer in **any order**.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

![[7_Backtracking-20240920212144499.webp]]

```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        backtracking(digits, 0);
        return results;
    }

private:
    const string letterMap[10] = {
        "", // 0
        "", // 1
        "abc", // 2
        "def", // 3
        "ghi", // 4
        "jkl", // 5
        "mno", // 6
        "pqrs", // 7
        "tuv", // 8
        "wxyz", // 9
    };

    void backtracking(const string& digits, int i)
    {
        if(digits.size() == i)
        {
            if(i > 0)
                results.push_back(path);
            return;
        }

        const string& letters = letterMap[digits[i] - '0'];
        for(const char& c : letters)
        {
            path.push_back(c);
            backtracking(digits, i + 1);
            path.pop_back();
        }
    }

private:
    vector<string> results;
    string path;
};
```

### 39. Combination Sum

Given an array of **distinct** integers `candidates` and a target integer `target`, return _a list of all **unique combinations** of_ `candidates` _where the chosen numbers sum to_ `target`_._ You may return the combinations in **any order**.

The **same** number may be chosen from `candidates` an **unlimited number of times**. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

The test cases are generated such that the number of unique combinations that sum up to `target` is less than `150` combinations for the given input.

>[!important] the `startIndex` passed to the next is just current `i`

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
    {
        backtracking(candidates, 0, target, 0);
        return res;
    }
private:

    void backtracking(vector<int>& candidates, int sum, int target, int startIndex)
    {
        if(sum >= target)
        {
            if(sum == target)
                res.push_back(path);
            return;
        }

        for(int i = startIndex; i < candidates.size(); ++i)
        {
            path.push_back(candidates[i]);
            sum += candidates[i];
            backtracking(candidates, sum, target, i);
            sum -= candidates[i];
            path.pop_back();
        }
    }


private:
    vector<int> path;
    vector<vector<int>> res;
};
```

### TODO 40 Combination Sum II

Given a collection of candidate numbers (`candidates`) and a target number (`target`), find all unique combinations in `candidates` where the candidate numbers sum to `target`.

Each number in `candidates` may only be used **once** in the combination.

**Note:** The solution set must not contain duplicate combinations.

![[7_Backtracking-20240920215626327.webp]]

>[!important] 强调一下，树层去重的话，需要对数组排序！
>如果`candidates[i] == candidates[i - 1]` 并且 `used[i - 1] == false`，就说明：前一个树枝，使用了candidates[i - 1]，也就是说同一树层使用过candidates[i - 1]。

```cpp
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int sum, int startIndex, vector<bool>& used) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            // used[i - 1] == true，说明同一树枝candidates[i - 1]使用过
            // used[i - 1] == false，说明同一树层candidates[i - 1]使用过
            // 要对同一树层使用过的元素进行跳过
            if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false) {
                continue;
            }
            sum += candidates[i];
            path.push_back(candidates[i]);
            used[i] = true;
            backtracking(candidates, target, sum, i + 1, used); // 和39.组合总和的区别1，这里是i+1，每个数字在每个组合中只能使用一次
            used[i] = false;
            sum -= candidates[i];
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<bool> used(candidates.size(), false);
        path.clear();
        result.clear();
        // 首先把给candidates排序，让其相同的元素都挨在一起。
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0, used);
        return result;
    }
};
```

## 切割 Partition

>[!summary] Partition means, not abandon, each element should be used. 
### 131. Palindrome Partitioning
Given a string `s`, partition `s` such that every substring of the partition is a **palindrome**. Return _all possible palindrome partitioning of_ `s`.

```cpp
class Solution {
public:
    vector<vector<string>> partition(string s) {
        backtracking(s, 0);
        return results;
    }

private:
    bool isPalindrome(const string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }

    void backtracking(const string& s, int startIndex)
    {
        if(startIndex >= s.size())
        {
            results.push_back(path);
            return;
        }

        for(int i = startIndex; i < s.size(); ++i)
        {
            if(!isPalindrome(s, startIndex, i))
                continue;

            path.push_back(s.substr(startIndex, i - startIndex + 1));
            backtracking(s, i + 1);
            path.pop_back();
        }
    }

private:
    vector<string> path;
    vector<vector<string>> results;
};
```

### 93 Restore IP Address
A **valid IP address** consists of exactly four integers separated by single dots. Each integer is between `0` and `255` (**inclusive**) and cannot have leading zeros.

- For example, `"0.1.2.201"` and `"192.168.1.1"` are **valid** IP addresses, but `"0.011.255.245"`, `"192.168.1.312"` and `"192.168@1.1"` are **invalid** IP addresses.

Given a string `s` containing only digits, return _all possible valid IP addresses that can be formed by inserting dots into_ `s`. You are **not** allowed to reorder or remove any digits in `s`. You may return the valid IP addresses in **any** order.

```cpp
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        backtracking(s, 0, 0);
        return result;
    }

private:

    // 判断字符串s在左闭右闭区间[start, end]所组成的数字是否合法
    bool isValid(const string& s, int start, int end) {
        if (start > end) {
            return false;
        }
        if (s[start] == '0' && start != end) { // 0开头的数字不合法
                return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }

    void backtracking(string & s, int startIndex, int numPoints)
    {
        if(numPoints == 3)
        {
             // 判断第四段子字符串是否合法，如果合法就放进result中
            if (isValid(s, startIndex, s.size() - 1)) {
                result.push_back(s);
            }
            return;
        }

        for(int i = startIndex; i < s.size() && i < startIndex + 3; ++i)
        {
            if(!isValid(s, startIndex, i))
            {
                continue;
            }

             s.insert(s.begin() + i + 1 , '.');
             ++numPoints;
             backtracking(s, i + 2, numPoints);
             --numPoints;
             s.erase(s.begin() + i + 1); 
        }


    }

    vector<string> result;
};
```

## 子集

>[!summary] 如果把 子集问题、组合问题、分割问题都抽象为一棵树的话
>**那么组合问题和分割问题都是收集树的叶子节点，而子集问题是找树的所有节点！**

### 78 Subsets
Given an integer array `nums` of **unique** elements, return _all possible_ _subsets_ _(the power set)_.
The solution set **must not** contain duplicate subsets. Return the solution in **any order**.

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
private:
    vector<vector<int>> result;
    vector<int> path;
    
    void backtracking(vector<int>& nums, int startIndex) {

        result.push_back(path); // 收集子集，要放在终止添加的上面，否则会漏掉自己

        if(startIndex >= nums.size())
        {
            return;
        }

        for(int i = startIndex; i < nums.size(); ++i)
        {
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
};
```


### 90. Subsets II
Given an integer array `nums` that may contain duplicates, return _all possible_ _subsets_ _(the power set)_. 
The solution set **must not** contain duplicate subsets. Return the solution in **any order**.

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size(), false);
        backtracking(nums, used, 0);
        return results;
    }
private:
    vector<vector<int>> results;
    vector<int> path;
    
    void backtracking(const vector<int>& nums, vector<bool>& used, int startIdx)
    {
        results.push_back(path);
        if(startIdx >= nums.size())
        {
            return;
        }

        for(int i = startIdx; i < nums.size(); ++i)
        {
            if(i > 0 && nums[i] == nums[i - 1] && !used[i - 1])
            {
                continue;
            }

            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used, i + 1);
            used[i] = false;
            path.pop_back();
        }
    }
};
```

### 491 Non-decreasing Subsequences

Given an integer array `nums`, return _all the different possible non-decreasing subsequences of the given array with at least two elements_. You may return the answer in **any order**.

>[!tip] 
>最长子序列，要保持原有顺序，因此不可以排序，所以去重方法要改变
>每一层记录同元素是否使用过，保证同层
```cpp
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {

        backtracking(nums, 0);
        return results;

    }
private:

    void backtracking(const vector<int>& nums, int startIndex)
    {
        if(path.size() > 1)
        {
            results.push_back(path);
        }

        if(startIndex >= nums.size())
        {
            return;
        }

        unordered_set<int> uset; // 使用set来对本层元素进行去重
        for(int i = startIndex; i < nums.size(); ++i)
        {
            if((!path.empty() && path.back() > nums[i])
                || uset.find(nums[i]) != uset.end())
                continue;
        

            path.push_back(nums[i]);
            uset.insert(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> results;
    vector<int> path;
};
```



## 排列

### 46 Permutations
Given an array `nums` of distinct integers, return all the possible permutations. You can return the answer in **any order**.

>[!Tip] 全排序，需要每个元素都需要在第一个位置, ... 每个位置出现，所以每一层都需要从头遍历，所以不需要 `startIndex`, 但是不可以重复，所以需要标记是否当前`path`已经使用过 

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return results;
    }

private:
    void backtracking(const vector<int>& nums, vector<bool>& used)
    {
        if(path.size() == nums.size())
        {
            results.push_back(path);
            return;
        }

        for(int i = 0; i < nums.size(); ++i)
        {
            if(used[i])
                continue;
            
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }

    vector<int> path;
    vector<vector<int>> results;
};
```