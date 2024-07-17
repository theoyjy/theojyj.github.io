>[!Info] An array is a collection of the same type of data stored on a contiguous memory space

# Binary Search
*leetcode 704*

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
### 35 Insert value or return existed index in an ascending array
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

## 34 Find First and Last Position of 

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

# Dual Pointer Method
*leetcode 27*

>[!Definition] A fast pointer and a slow pointer can do the work of two loops under one loop

## Fast and Slow Pointers
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
```
### Simulation:
remove value: 3
f
3 2 2 3 `f++`
s

   f
3 2 2 3 `nums[f] != 3: nums[s++] = 2; f++`
s

    f
2 2   2  3 `nums[f] != 3; nums[s++] = 2; f++`
   s
   
       f
2 2   2 3 `f++`
     s

`return 2`

## Front and Back Pointers
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
```

### Simulation:

Remove Value: 3

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
   
`return ++1;`