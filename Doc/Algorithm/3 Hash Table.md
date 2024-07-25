_[homepage](index.md)_

>[!Info] A Hash table is defined as a data structure used to **insert, look up, and remove key-value pairs quickly**.
>It operates on the [hashing concept](https://www.geeksforgeeks.org/what-is-hashing/), where each key is translated by a hash function into a distinct index in an array. The index functions as a storage location for the matching value. In simple words, it maps the keys with the value.

### When to use hash table

>When we want to find out if an element appears before or whether an element exists in the set.


### Load Factor

* It is determined by:
	1. number of elements are kept
	2. size of the hash table.
* When load factor is *high*: the table may be cluttered and have longer search times and collisions.

### Collision resolution techniques:
It happens when two or more keys  points to the same array index.
1. **Open Addressing**
   The hash function is applied to the subsequent slots until one is left empty. There are various ways to use this approach: double hashing, **linear probing**, and quadratic probing.
2. **Separate Chaining**:
   In separate chaining, a linked list of objects that hash to each slot in the hash table is present. Two keys are included in the linked list if they hash to the same slot. This method is rather simple to use and can manage several collisions.
3. **Robin Hood hashing**: 
   To reduce the length of the chain, collisions in Robin Hood hashing are addressed by switching off keys. The algorithm compares the distance between the slot and the occupied slot of the two keys if a new key hashes to an already-occupied slot. The existing key gets swapped out with the new one if it is closer to its ideal slot. This brings the existing key closer to its ideal slot. This method has a tendency to cut down on collisions and average chain length.
   
### Hashing in Data structure
1. array
2. set
3. map
### `set` and `map` in C++

#### `set`

|                    | Underlying Implementation | ordered   | repeatable | modifiable | query efficiency | addition and deletions efficieny |
| ------------------ | ------------------------- | --------- | ---------- | ---------- | ---------------- | -------------------------------- |
| std::set           | Red–black tree            | Ordered   | No         | No         | O(log n)         | O(log n)                         |
| std::multiset      | Red–black tree            | Ordered   | Yes        | No         | O(log n)         | O(log n)                         |
| std::unordered_set | Hash Table                | Unordered | No         | No         | **O(1)**         | **O(1)**                         |

#### `map`

|                    | Underlying Implementation | ordered | repeatable | modifiable | query efficiency | addition and deletions efficieny |
| ------------------ | ------------------------- | ------- | ---------- | ---------- | ---------------- | -------------------------------- |
| std::map           | Red–black tree            | Ordered | No         | No         | O(log n)         | O(log n)                         |
| std::multimap      | Red–black tree            | Ordered | Yes        | No         | O(log n)         | O(log n)                         |
| std::unordered_map | Hash Table                | Unorde  | No         | No         | O(1)             | O(1)                             |


## Array as Hash Table

>[!Important] Only using array as hash table when keys' range is limited
### 242 Valid Anagram
Given two string `s` and `t`, return true if `t` is an anagram of `s`, and `false` otherwise.

>the range of the hashes is just from `a` to `z`, which is quite small. So we define an array as a hash table, the value of each key is just the occurrence of each letter

```cpp
bool isAnagram(string s, string t) {

	int record[26] = {0};
	// get occurrences of each letter in `s`
	for(char i : s)
	{
		++record[i - 'a'];
	}

	// remove letters appeared in `t`
	for(char i : t)
	{
		if(--record[i - 'a'] < 0) // `t` use more of a specific letter than 
			return false;         // `s`, so they cann't be an anagram
	}

	for(int i : record)
	{
		if(i != 0) // `t` couldn't use all of the letters in `s`
			return false;
	}
	return true;
}
```

### 383. Ransom Note
Given two strings `ransomNote` and `magazine`, return `true` _if_ `ransomNote` _can be constructed by using the letters from_ `magazine` _and_ `false` _otherwise_.

Each letter in `magazine` can only be used once in `ransomNote`.

>[!Tip] please notice the range of key is limited to lowercase letters, so we can achieve the hash table with array to save space and time.

```cpp
bool canConstruct(string ransomNote, string magazine) {
	int record[26] = {0};
	for(char c : magazine)
	{
		++record[c - 'a'];
	}

	for(char c : ransomNote)
	{
		if(record[c - 'a'] <= 0)
			return false;
		--record[c - 'a'];
	}
	return true;
}
```

## `unordered_set` and `unordered_map` as Hash Table

>[!Tip] If the hashes are relatively small, particularly scattered, and span a very large area, using an array results in a huge waste of space. 
>We should be considering between `unordered_set` and `unordered_map`

### 349. Intersection of Two Arrays
Given two integer arrays `num1` and `num2`, return an array of their intersection. Each element in the result must be **unique** and you may return in any order.

> The range of values from the two arrays could be very large and scattered, while it requires the **uniqueness**, it only left us with `unordered_set`

```cpp
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
	unordered_set<int> result;
	unordered_set<int> nums1Set(nums1.begin(), nums1.end());

	for(int i : nums2)
	{
		if(nums1Set.find(i) != nums1Set.end())
			result.emplace(i);
	}
	
	return vector<int>(result.begin(), result.end());
}
```

### 202 Happy Number
Write an algorithm to determine if a number `n` is happy.

A **happy number** is a number defined by the following process:

- Starting with any positive integer, replace the number by the sum of the squares of its digits.
- Repeat the process until the number equals 1 (where it will stay), or it **loops endlessly in a cycle** which does not include 1.
- Those numbers for which this process **ends in 1** are happy.

Return `true` _if_ `n` _is a happy number, and_ `false` _if not_.

> The question gives the tip that if a number is not happy, it will loop endlessly, so we just need to know if the sum appears before. so `unordered_set` records the sums along the calculations

```cpp
int getSum(int n)
{
	int sum = 0;
	while(n)
	{
		sum += (n % 10) * (n % 10);
		n /= 10;
	}
	return sum;
}

bool isHappy(int n) 
{
	unordered_set<int> sums;
	int sum = getSum(n);
	while(sum != 1)
	{
		if(sums.find(sum) != sums.end())
		{
			return false;
		}
		sums.emplace(sum);
		sum = getSum(sum);
	}
	return true;
}
```


### 1 Tow Sum
Given an array of integers `nums` and an integer `target`, return _indices of the two numbers such that they add up to `target`_.

You may assume that each input would have **_exactly_ one solution**, and you may not use the _same_ element twice.

You can return the answer in any order.

```cpp
/*
* iterate the array, get the remain number of each element, if that number
* was in the array, return the pair
* Otherwise, record current element with its index for future returning.
*/
vector<int> twoSum(vector<int>& nums, int target) {
	unordered_map<int, int> map;
	for(int i = 0; i < nums.size(); ++i)
	{
		if(auto itr = map.find(target - nums[i]); itr != map.end())
		{
			return {itr->second, i};
		}
		map.emplace(nums[i], i);
	}
	return {-1, -1};
}
```

### 454 4Sum II
Given four integer arrays `nums1`, `nums2`, `nums3`, and `nums4` all of length `n`, return the number of tuples `(i, j, k, l)` such that:
- `0 <= i, j, k, l < n`
- `nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0`
#### Steps
1. using an `unordered_map` records the sum from an element from `nums1` and another from `nums2` as key, and the occurrence of the sum as value
2. Iterating `nums3` and `nums4`, find if `0 - nums3[i] - nums4[j]` exists in the map.

```cpp
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
	unordered_map<int, int> sum12;
	for(int i : nums1)
		for(int j : nums2)
			++sum12[i+j];

	int count = 0;
	for(int i : nums3)
	{
		for(int j : nums4)
		{
			auto iter = sum12.find(0 - i - j);
			if(iter != sum12.end())
			{
				count += iter->second;
			}
		}
	}
	return count;
}
```

## Hash alike questions
### 15 3Sum
Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must not contain duplicate triplets.

>[!caution] It's easy to be mislead to use hash table to record the sum of first two numbers.
>But the question requires **unique triplets**, which could cost checking duplication every time we find a new combination. As a result, we better solve this by dual pointers.

1. Since it doesn't require the indexes of the elements, we can `sort` the array firstly
2. we have i starts from `0` towards `nums.size() - 3`
	1. make sure that `nums[i]` is different from `nums[i-1]` to prevent duplication
3. we have `left = i+1; right = nums.size() - 1`
4. Keeps testing if `nums[i] + nums[left] + nums[right] == 0`
	1. if equals, that means we find a unique result, record it, then moves `left` and `right` till unidentical value
	2. if greater than 0, `--right`
	3. if lesser than 0, `++left`

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());
	for(int i = 0; i < nums.size() - 2; ++i)
	{
		// remove duplication of i
		if(i > 0 && nums[i - 1]==nums[i])
			continue;

		int left = i + 1, right = nums.size() - 1;
		while(left < right)
		{
			int sum = nums[i] + nums[left] + nums[right];
			if(sum == 0)
			{
				res.push_back({nums[i], nums[left], nums[right]});
				// remove duplications of left and right
				while (right > left && nums[right] == nums[right - 1]) --right;
				while (right > left && nums[left] == nums[left + 1]) ++left;
				--right;
				++left;
			}
			else if(sum < 0)
				++left;
			else
				--right;
		}
	}
	return res;
}
```

### 18 4Sum
Given an array `nums` of `n` integers, return _an array of all the **unique** quadruplets_ `[nums[a], nums[b], nums[c], nums[d]]` such that:

- `0 <= a, b, c, d < n`
- `a`, `b`, `c`, and `d` are **distinct**.
- `nums[a] + nums[b] + nums[c] + nums[d] == target`

You may return the answer in **any order**.

>[!Tip] Still use dual pointers as above one

```cpp
vector<vector<int>> fourSum(vector<int>& nums, int target) {
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());
	
	// be careful size() return uint, should convert to int for minus
	int size = nums.size(); 
	for(int i = 0; i < size - 3; ++i)
	{
		// pruning
		if(nums[i] > target && target >= 0)
			break;
		// avoid duplication
		if(i > 0 && nums[i] == nums[i - 1])
			continue;
		for(int j = i + 1; j < size - 2; ++j)
		{
			// pruning
			if(nums[i] + nums[j] > target && target >= 0)
				break;
			// avoiding duplication
			if(j > i + 1 && nums[j] == nums[j - 1])
				continue;

			int left = j + 1, right = size - 1;
			while(left < right)
			{
				// sum may be out of int's range
				long sum = (long)nums[i] + nums[j] + nums[left] + nums[right];
				if(sum == target)
				{
					res.push_back({nums[i], nums[j], nums[left], nums[right]});
					// avoiding duplication
					while(left < right && nums[right] == nums[right - 1]) --right;
					while(left < right && nums[left] == nums[left + 1]) ++left;
					--right;
					++left;
				}
				else if(sum < target)
					++left;
				else
					--right;
			}
		}
	}
	return res;
}
```