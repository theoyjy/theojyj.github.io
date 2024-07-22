_[homepage](index.md)_

>[!Info] An array is a collection of the same type of data stored on a contiguous memory space

# Binary Search

*leetcode 704*
Given an array of integers `nums` which is sorted in ascending order, and an integer `target`, write a function to search `target` in `nums`. If `target` exists, then return its index. Otherwise, return `-1`.

>[!Tip] Preventing `left + right` is out of the range of int, so we have
>```cpp
int mid = left + ((right - left) / 2)
>```

## Left-closed and right-closed interval [left, right]

* `left == right` is meaning, so `while(left <= right)`
* Since `right` is valid index, `if(midValue < target) right = mid - 1;` 
  ```cpp
	while(left <= right)
	{
		int mid = left + ((right -left) >> 1);
		if(/*equal*/)
			return mid;
		else if(/*less*/)
			left = mid + 1;
		else // greater
			right = mid - 1;
	}
	return -1;
	```

## Left-closed, right-open Interval [left, right)

* `left == right` is invalid, so `while(left < right)`
* since `right` is invalid index, `if(midValue < target) right = mid;`
  ```cpp
  		if(/*equal*/)
			return mid;
		else if(/*less*/)
			left = mid + 1;
		else // greater
			right = mid;
	```

## Extension Questions
### 35  Search Insert Position
Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

*You must write an algorithm with `O(log n)` runtime complexity.*

```cpp
int searchInsert(vector<int>& nums, int target) {
	int left = 0, right = nums.size() - 1;
	while(left <= right)
	{
		int mid = left + ((right - left) >> 1);
		cout << left << right << endl;
		if(nums[mid] == target)
			return mid;
		else if(nums[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}

	// now l > r, three situations:
	// [0, -1] -> 0
	// [x, x - 1] -> x
	// [arraySize, arraySize - 1]
	return left;

}
```

### 34 Find First and Last Position of Elements in Sorted Array
Given an array of integers `nums` sorted in non-decreasing order, find the starting and ending position of a given `target` value.

If `target` is not found in the array, return `[-1, -1]`.

You must write an algorithm with `O(log n)` runtime complexity.

```cpp
vector<int> searchRange(vector<int>& nums, int target) {
	int leftBorder = getBorder(nums, target, true);
	int rightBorder = getBorder(nums, target, false);
	if(leftBorder == -2 || rightBorder == -2)   return {-1, -1};
	if (rightBorder - leftBorder > 1) return {leftBorder + 1, rightBorder - 1};
	return {-1, -1};
}



/*
* -2 not set
*/

int getBorder(vector<int>& nums, int target, bool bLeftOrRight)
{
	int left = 0, right = nums.size() - 1;
	int border = -2; // not set
	while(left <= right)
	{
		int mid = left + ((right - left) >> 1);
		// cout << left << right << endl;
		if(!bLeftOrRight) // calc right border
		{
			if(nums[mid] > target)
				right = mid - 1;
			else // let left pointer move towards right border, so left move whenever nums[mid] <= target
			{
				left = mid + 1;
				border = left;
			}
		}

		else // calc for left border
		{
			if(nums[mid] < target)
				left = mid + 1;
			else // let right pointer move towards left border, so right move whenever nums[mid] >= target
			{
				right = mid - 1;
				border = right;
			}
		}
	}
	return border;
}
```

### 59 Spiral Matrix
Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.


>[!Caution] Consider how to divide the intervals
>1. 4 loops for four sides of a square
>2. each loop is limited to a left-close right-open interval, the last number letting the next loop handle it.

![[Array-20240718174307980.webp]]
```cpp
vector<vector<int>> generateMatrix(int n) {
	vector<vector<int>> res(n, vector<int>(n, 0)); // 2 dimension array
	int startx = 0, starty = 0; // start position of each loop
	int mid = n / 2; // center index
	int loop = n / 2; // number of loops, if n is odd, extra care at center
	int count = 1; // number to fill in
	int offset = 1; // limit the length of row and  columns
	int i,j;
	while (loop --) {
		i = startx;
		j = starty;
		auto setValueWithLog = [&res, &i, &j, &count]()
		{
			res[i][j] = count;
			cout << "Set(" << i << ", " << j << ") = " << count << endl;
			++count;
		};
		
		// Left-closed (draw), right-open(not draw, next for loop will fill it for us)
		// left -> right
		for (; j < n - offset; j++)
			setValueWithLog();
		cout << endl;
		
		// up -> down
		for (; i < n - offset; i++)
			setValueWithLog();
		cout << endl;

		// right -> left
		for (; j > starty; j--)
			setValueWithLog();
		cout << endl;

		// down -> up
		for (; i > startx; i--)
			setValueWithLog();

		// one loop finished, update the start of next loop
		++startx;
		++starty;
		++offset;
	}
	
	// if n is odd, extra care at the center
	if (n % 2) {
		res[mid][mid] = count;
	}
	return res;
}
```
# Dual Pointer Method


>[!Definition] A fast pointer and a slow pointer can do the work of two loops under one loop

## Fast and Slow Pointers

### 27 Remove Element
Given an integer array `nums` and an integer `val`, remove all occurrences of `val` in `nums` in-place. The order of the elements may be changed. Then return _the number of elements in_ `nums` _which are not equal to_ `val`.

Consider the number of elements in `nums` which are not equal to `val` be `k`, to get accepted, you need to do the following things:

- Change the array `nums` such that the first `k` elements of `nums` contain the elements which are not equal to `val`. The remaining elements of `nums` are not important as well as the size of `nums`.
- Return `k`.

```cpp
int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); fast++) {
            if (val != nums[fast]) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }

Simulation:

f
3 2 2 3 `f++`
s

   f
3 2 2 3 `nums[f] != 3: nums[s++] = 2; f++`
s

    f
2 2 2  3 `nums[f] != 3; nums[s++] = 2; f++`
  s
   
      f
2 2 2 3 `f++`
    s

`return 2`
```


## Front and Back Pointers

### 27 Remove Element

```cpp
int removeElement(vector<int>& nums, int val) {
	int left = 0, right = nums.size() - 1;
	while(left <= right){
		if(nums[left] == val){
			nums[left] = nums[right];
			right--;
		}else {
			// 这里兼容了right指针指向的值与val相等的情况
			left++;
		}
	}
	return left;
}

Simulation:
      r
3 2 2 3  `nums[0] = nums[3] = 3`
l

    r
3 2 2 3 `nums[0] = nums[2] = 2`
l

   r
2 2 2 3
l

   r
2 2 2 3 `left == right: left++;`
   l
   
return ++1;
```

### 977 Square of sorted non-descending array
Given an integer array `nums` sorted in **non-decreasing** order, return _an array of **the squares of each number** sorted in non-decreasing order_.

```cpp
vector<int> sortedSquares(vector<int>& nums) {
	int l = 0, r = nums.size() - 1;
	vector<int> res(r + 1);
	int arrayIndex = r;
	while(l <= r)
	{
		if(abs(nums[l]) >= abs(nums[r]))
		{
			res[arrayIndex--] = nums[l] * nums[l];
			++l;
		}
		else
		{
			res[arrayIndex--] = nums[r] * nums[r];
			--r;
		}
	}
	return res;
}

Simulation:
1.
          r
-4 -1 0 3 10  `(-4)^2 < 10^2 : res[i--] = (10^2); r--`
l

2.             res:
        r    |       i     |
-4 -1 0 3 10 | _ _ _ _ 100 |`(-4)^2 > 3^2 : res[i--]=(-4)^2; l++`
l            |             |

3.             res:
        r    |     i        |
-4 -1 0 3 10 | _ _ _ 16 100 |`(-1)^2 < 3^2 : res[i--]=(3)^2; r--`
    l        |              |

4.             res
      r      |   i          |
-4 -1 0 3 10 | _ _ 9 16 100 |`(-1)^2 > 0^2 : res[i--]=(-1)^2; l++`
    l        |              |

5.             res
      r      | i            |
-4 -1 0 3 10 | _ 1 9 16 100 |`(0)^2 > 0^2 : res[i--]=(0)^2; l++`
      l      |              |

res:
0 1 9 16 100
```

## Sliding Window

>[!important] The so-called sliding window is a constant adjustment of the starting and ending positions of the subsequence to arrive at the result we want.

### 209 Minimum Size Subarray Sum
Given an array of positive integers `nums` and a positive integer `target`, return _the **minimal length** of a_ _subarray_ _whose sum is greater than or equal to_ `target`. If there is no such subarray, return `0` instead.
 
```cpp
int minSubArrayLen(int target, vector<int>& nums) {
	int l = 0, r = 0;
	int minLen = INT32_MAX;
	int sum = 0;
	while(r < nums.size())
	{
		sum += nums[r];
		while(l <= r && sum >= target)
		{
			if(minLen > (r - l) + 1)
				minLen = r - l + 1;
			sum -= nums[l++];
		}
		++r;
	}
	return minLen == INT32_MAX ? 0 : minLen;
}

Simulation:
target = 7

r
2 3 1 2 4 3
l

      r
2 3 1 2 4 3 `sum = 8 > target: minlen = 4;`
l
```

