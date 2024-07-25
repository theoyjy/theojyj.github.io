_[homepage](index.md)_

### 344.Reverse String
Write a function that reverses a string. The input string is given as an array of characters `s`.

You must do this by modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm) with `O(1)` extra memory.
```cpp
void reverseString(vector<char>& s) {
	int i = 0, j = s.size() - 1;
	while(i < j)
	{
		swap(s[i++], s[j--]);
	}
}
```

### 541. Reverse String II
Given a string `s` and an integer `k`, reverse the first `k` characters for every `2k` characters counting from the start of the string.

If there are fewer than `k` characters left, reverse all of them. If there are less than `2k` but greater than or equal to `k` characters, then reverse the first `k` characters and leave the other as original.

> [!info] `reverse(obj.begin() + left, obj.begin() + right)` is coped with left-close and right-open rule

```cpp
string reverseStr(string s, int k) {
	for(int i = 0; i < s.size(); i += 2 * k)
	{
		if(i + k > s.size())
		{
			reverse(s.begin() + i, s.end());
		}
		else
		{
			reverse(s.begin() + i, s.begin() + i + k);
		}            
	}
	return s;
}
```

### Kama 54 Substitute numbers
Given a string `s` that contains lowercase alphabetic and numeric characters, write a function that leaves the alphabetic characters in the string unchanged and replaces each numeric character with "number". For example, for the input string “a1b2c3”, the function should convert it to “anumberbnumbercnumber”.

```cpp
void substitudeNumbers(string& s)
{
    auto isNumber = [](const char& c)
    {
        return c >= '0' && c <= '9';
    };
    
    int count = 0;
    for(const char & c : s)
    {
        if(isNumber(c))
            ++count;
    }

	// expand s to desired length otherwise it have to expand everytime
	// we replace a numeric letter with string "number"
    int oriSize = s.size();
    int newSize = oriSize + count * 5;
    s.resize(newSize, ' ');
    
    int i = oriSize - 1, j = newSize - 1;
    while(i >= 0)
    {
        if(isNumber(s[i]))
        {
            s[j--] = 'r';
            s[j--] = 'e';
            s[j--] = 'b';
            s[j--] = 'm';
            s[j--] = 'u';
            s[j--] = 'n';
        }
        else
        {
            s[j--] = s[i];
        }
        --i;
    }
}
```

### 151 Reverse Words in a String
Given an input string `s`, reverse the order of the **words**.

A **word** is defined as a sequence of non-space characters. The **words** in `s` will be separated by at least one space.

Return _a string of the words in reverse order concatenated by a single space._

**Note** that `s` may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

```cpp
void removeExtraSpace(string& s)
{
	int slow = 0;
	for(int i = 0; i < s.size(); ++i)
	{
		if(s[i] == ' ')
			continue;

		if(slow != 0) s[slow++] = ' '; // add space between words
		while(i < s.size() && s[i] != ' ')
			s[slow++] = s[i++];
	}
	s.resize(slow);
}

string reverseWords(string s) {
	// 1. remove extra spaces
	removeExtraSpace(s);

	// 2. reverse whole string
	reverse(s.begin(), s.end());

	// 3. reverse each word
	int i = 0;
	const int len = s.size();
	while(i < len)
	{
		int j = i;
		while(j < len && s[j] != ' ')
			++j;

		reverse(s.begin() + i, s.begin() + j);
		i = j + 1;
	}
	return s;
}
```

### Kama 55 Rotate string to right
The right-rotation operation of a string involves shifting a number of characters from the end of the string to the front of the string. Given a string `s` and a positive integer `k`, write a function that implements the right-rotation operation on a string by shifting the trailing `k` characters to the front of the string. 

For example, for the input string “abcdefg” and integer 2, the function should convert it to “fgabcde”.

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    string s;
    int n;
    cin >> n >> s;
	// reverse whole string
    reverse(s.begin(), s.end());
    // reverse front n substring
    reverse(s.begin(), s.begin() + n);
    // reverse the rest substring
    reverse(s.begin() + n, s.end());
    
    cout << s;
    return 0;
}
```

### 28 Find the Index of the First Occurrence in a String(**KMP**)
Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.

> [!Warning] `next` array
> `next` is trying to mean that when string matching fails at index `i`, go testing at the previous index `next[i]`. `next[i]` records the **length** of the **longest equal prefix and suffix** in range of `[0, i - 1]`. 
> #### Sample of getting `next` array
> ```cpp
> s = "aabaaf"
> next[0] = 0;
> 
> // a a b a a f
> // 0                s[i] == s[j]: ++j; next[1] = 1; ++i
> // j i
> 
> // a a b a a f
> // 0 1              while(j > 0 && s[j] != s[i]) j = next[j - 1] = 0; next[2] = 0; ++i
> //   j i
> 
> // a a b a a f
> // 0 1 0            s[j] == s[i]; ++j; next[3] = 1; ++i
> // j     i
> 
> // a a b a a f
> // 0 1 0 1          s[j] == s[i]; ++j; next[4] = 2; ++i
> //   j     i
> 
> // a a b a a f
> // 0 1 0 1 2        while(j > 0 && s[j] != s[i]) j = next[j - 1] = 0; next[5] = 0; ++i
> //   j       i
> 
> // a a b a a f
> // 0 1 0 1 2 0
> ```

> [!Tip] `strStr()`
> Comparing an array `haystack` to `needle` is quite same as the process of generating `next` array. Except that we are comparing `haystack[i]` to `needle[j]`, where i would be steadily increasing by `1` each iteration, yet `j` goes backwards `j = next[j - 1]` when unmatching.

```cpp
vector<int> getNext(const string& s)
{
	vector<int> next(s.size(), 0); // useful records when fails matching at 
						     // index i, it can keep comparing from next[i]

	// j is at the end of prefix
	// i is at the start of suffix
	for(int i = 1, j = 0; i < s.size(); ++i)
	{
		// prefix does not match with suffix, j goes backwards, prefix shrinks
		while(j > 0 && s[j] != s[i])
		{
			j = next[j - 1];
		}

		if(s[j] == s[i])
		{
			++j;
		}
		next[i] = j;
	}
	return next;
}

int strStr(string haystack, string needle) {
	vector<int> next = getNext(needle);
	// matching process is quite same except that, `getNext` is comparing
	// needle with itself, now we are comparing needle with haystack
	for(int i = 0, j = 0; i < haystack.size(); ++i)
	{
		while(j > 0 && haystack[i] != needle[j])
		{
			j = next[j - 1];
		}

		if(haystack[i] == needle[j])
		{
			++j;
		}

		if(j == needle.size())
			return i - j + 1;
	}
	return -1;
}
```