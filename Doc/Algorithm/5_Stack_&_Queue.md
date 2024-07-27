_[homepage](../../index.md)_

> [!info] Container Adaptor
> Stack and queue are not containers, they are container adapters, which can be implemented with different kinds of containers. They don't provide iterators.

### 232 Implement Queue using Stacks

```cpp
class MyQueue {
public:

    MyQueue() {

    }
    
    void push(int x) {
        stIn.push(x);
    }

    int pop() {
        move();
        int top = stOut.top();
        stOut.pop();
        return top;
    }

    int peek() {
        move();
        return stOut.top();
    }

    bool empty() {
        return stIn.empty() && stOut.empty();
    }

private:
    void move()
    {
        if(stOut.empty())
        {
            while(stIn.size())
            {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
    }

private:
    stack<int> stIn;
    stack<int> stOut;

};
```

### 225 Implement Stack using Queues

```cpp
class MyStack {
public:

    MyStack() {

    }

    void push(int x) {
        que.push(x);
    }

    int pop() {
        int size = que.size();
        while(size > 1)
        {
            que.push(que.front());
            que.pop();
            --size;
        }

        int top = que.front();
        que.pop();
        return top;

    }

    int top() {
        return que.back();
    }

    bool empty() {
        return que.empty();
    }

private:
    queue<int> que;
};
```

### 20 Valid Parentheses
Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

```cpp
bool isValid(string s) {
	stack<char> st;
	unordered_map<char, char> pairs =
	{
		{')', '('},
		{']', '['},
		{'}', '{'}
	};

	for(const char& c : s)
	{
		if(c == '(' || c == '[' || c == '{')
		{
			st.push(c);
		}    
		else if(!st.empty())
		{
			auto iter = pairs.find(c); 
			if(iter == pairs.end() ||  iter->second != st.top())
				return false;
			
			st.pop();
		}
		else
			return false;
	}
	return st.empty();
}`
```

### 1047 Remove all adjacent duplicates in string
 A **duplicate removal** consists of choosing two **adjacent** and **equal** letters and removing them.
We repeatedly make **duplicate removals** on `s` until we no longer can.

**Example 1**
	`s = "abbaca"`
	`output = "ca"`
**Example 2**
	`s = "abbbaca"`
	`output = "abaca"`

```cpp
string removeDuplicates(string s) {
	stack<char> st;
	for(const char& c : s)
	{
		if(!st.empty() && st.top() == c)
		{
			st.pop();
		}
		else
		{
			st.push(c);
		}            
	}

	string res(st.size(), 0);
	for(int i = st.size() - 1; i >= 0; --i)
	{
		res[i] = st.top();
		st.pop();
	}
	return res;
}
```

### 150 Evaluate Reverse Polish Notation
The operator precedes the two operands.

**Example 2:**
	**Input:** tokens = ["4","13","5","/","+"]
	**Output:** 6
	**Explanation:** (4 + (13 / 5)) = 6

**Example 3:**
	**Input:** tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
	**Output:** 22
	**Explanation:** ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
	= ((10 * (6 / (12 * -11))) + 17) + 5
	

```cpp
int evalRPN(vector<string>& tokens) {
	stack<long long> st;
	for(const string& s : tokens)
	{
		// every time encounters a operator
		if(s == "+" || s == "-" || s == "*" || s == "/")
		{
			// pop out the two operands
			// be careful about the first retrieved value should be dividend
			// so the first poped one should be operand2
			long long operand2 = st.top();
			st.pop();
			long long operand1 = st.top();
			st.pop();
			
			// evaluation:
			long long res = 0;
			char operation = s[0];
			switch(operation)
			{
				case '+':
					res = operand1 + operand2;
					break;
				case '-':
					res = operand1 - operand2;
					break;
				case '*':
					res = operand1 * operand2;
					break;
				case '/':
					res = operand1 / operand2;
					break;
			}

			// push result back for further calculatoin
			st.push(res);
		}
		else
		{
			// stoll: string to long long
			// stoi: string to int
			st.push(stoll(s));
		}
	}
	return st.top();
}
```


## Sliding Window

### 239 Sliding Window Maximum
You are given an array of integers `nums`, there is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return _the max sliding window_.

> [!info] Monotonic queue
> We don't need record every number in the window, we just need to keep a monotonic decreasing queue, the biggest number is always at the front. It works as:
> 1. the window moves right and `pop` out a number from front:
> 	1. if the popped number == the maximum in the window before, due to it's a monotonic decreasing array, the new front of the queue is the new maximum in the window before insertion of new value.
> 	2. if the popped number != max before sliding, that means the max should not be popped out yet, the original max is still the max before insertion
> 	3. Either way, we are pretty sure that the `front()` is the max after popping before inserting.
> 2. sliding windows `push` a new number to the back of the queue:
> 	1. keep `pop_back()` until the `back()` is `>=` the new number
> 	2. `push(newNumber)`
>>[!important] `multiset` can work as a monotonic queue
>>Since:
>>- when `insert` , it sorts automatically
>>- It allows duplicates as we need
>>- when `erase(find(toBeErasedValue))`, it sorts automatically
>>- we can easily retrieve smallest number `rbegin()` or smallest number `begin()`

#### Monotonic Queue implemented by `deque`

```cpp
class MonotonicQueue
{
public:
	// implemented by deque, we assign front as pop end
	// back as insertion end
	deque<int> que;
	
	//          -------------- 
	// front  <- ..|..|..|..     <- back
	//          --------------

	// pop from the front
	// since we are not recording every value in the window
	// we only pop when the value == front()
	void pop(int value) {
		if (!que.empty() && value == que.front()) {
			que.pop_front();
		}
	}

	// insert to the back
	// keeps poping out back elements until 
	// the back value is greater than new value, then we push the new value
	// this way, we make sure it's monotonic
	void push(int value) {
		while (!que.empty() && value > que.back()) {
			que.pop_back();
		}
		que.push_back(value);
	}

	int front() {
		return que.front();
	}
};

vector<int> maxSlidingWindowByMyMonotonicQueue(vector<int>& nums, int k) {
	vector<int> res;
	MonotonicQueue que;
	for(int i = 0; i < nums.size(); ++i)
	{
		// before i reaches k, sliding window is not full
		// should not pop yet
		 if(i >= k) 
			que.pop(nums[i - k]);
		
		// either windows is growing to size k
		// or move right
		// push either way
		que.push(nums[i]);

		// when window is full, starts output maximum
		if(i >= k - 1)
		{
			res.emplace_back(que.front());
		}
	}
	return res;
}
```

#### `multiset` as a monotonic queue
Since `multiset` just sorts automatically, we *insert every number in the sliding window to i*t. To achieve `pop()`, we `find(toBeErasedValue)` exactly where the number should be popped at, and `erase(itr)`. 

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {

	multiset<int> monotonicQueue;
	vector<int> res;

	for(int i = 0; i < nums.size(); ++i)
	{
		if(i >= k)
			monotonicQueue.erase(st.find(nums[i - k]));
		monotonicQueue.insert(nums[i]);

		if(i >= k - 1)
			res.emplace_back(monotonicQueue.rbegin());
	}
	return res;
}
```

## heap

### Compare function for `priority_queue`

>[!caution] 
>![[5_Stack_&_Queue-20240728021446094.webp]]
>From the above source code, we can see, the compare func in heap is to check whether there should be a swap. So **if it returns true, it means fails to meet condition, go swapping**, so:
>- max-heap: should be passed with compare func that returns true if `lhs < rhs`
>- min-heap: should be passed with compare func that returns true if `lhs > rhs`
>
>>However, this is opposite for `std::sort`, if the compare function returns true, it means the order of `lhs` and `rhs` is correct, no need for swaption.

### 347 Top k frequent elements
Given an integer array `nums` and an integer `k`, return _the_ `k` _most frequent elements_. You may return the answer in **any order**.

```cpp
 // we wanna min-heap, so pass greater comparation
class compareFrequencyPairs
{
public:
	bool operator()(const pair<int, int> & lhs, const pair<int, int> & rhs)
	{
		return lhs.second > rhs.second;
	}
};

vector<int> topKFrequent(vector<int>& nums, int k) {
	unordered_map<int, int> frequencies;
	for(const int & i : nums)
	{
		++frequencies[i];
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, compareFrequencyPairs> heap;
	for(auto& pair : frequencies)
	{
		heap.push(pair);
		if(heap.size() > k) // pop all the min and left with largest k pairs
			heap.pop();
	}

	vector<int> result(k);
	for (int i = k - 1; i >= 0; i--) {
		result[i] = heap.top().first;
		heap.pop();
	}
	return result;
}
```