_[homepage](../../index.md)_

>[!definition]
>Binary Tree is a tree data structure(non-linear) in which each node can have at most two children which are referred to as the left child and right child.
>The topmost node is called **root**, and the bottom-most nodes are called **leaves**.

## Terminology of Binary Tree
- Root: no incoming edge
- Child: has incoming edge
- **Sibling**: nodes having the same parent are sibling.
- **Degree of a node**: number of children of a particular parent. range from 0 to 2
- **Internal/External nodes**: leaf nodes are external nodes, non leaf nodes are internal nodes
- **height**: number of *edges* to reach the root. height of root is 0.
- **level**: number of *nodes* to reach the root. level of root is 0.

## Types of Binary Tree On the basis of the completion of levels

**1.  Perfect Binary Tree** 满二叉树
>[!definition] A Binary tree is a Perfect Binary Tree in which all the internal nodes have two children and all leaf nodes are at the same level.
>![[6_Binary_Tree-20240729190108875.webp|441]]
>When depth is $k$, there are $2^{k}-1$ nodes

**2. Complete Binary Tree** 完全二叉树
>[!definition] where all the levels are completely filled except possibly the last level and the last level has all keys as left as possible
>>[!info] ==heap is actual a complete binary tree== with guarantee on the orders between parents and children

>[!tip] Perfect Binary Tree vs Complete Binary Tree:
A **complete** binary tree of height $h$ is a perfect binary tree up to height $h-1$, and in the last level element are stored in left to right order.

**3. Balanced Binary Tree**
>[!definition] A binary tree is balanced if the height of the tree is O(Log n) where n is the number of nodes.
> For Example, the AVL tree maintains O(Log n) height by making sure that the difference between the heights of the left and right subtrees is at most 1. 
> Red-Black trees maintain O(Log n) height by making sure that the number of Black nodes on every root to leaf paths is the same and that there are no adjacent red nodes. 
> Balanced Binary Search trees are performance-wise good as they provide O(log n) time for search, insert and delete.
![[6_Binary_Tree-20240729192041229.webp]]
## Special Binary Trees

**1. ==Binary Search Tree(BST)==**
>[!Definition] Binary Search Tree has the following properties:
>- the left subtree of a node contains only nodes with keys lesser than the node's key
>- the right subtree of a node contains only nodes with keys greater than the node's key
>- the left and right subtree must also be a binary search tree

**2. AVL -- Balanced Search Tree**
>[!Definition] AVL tree is a self-balancing Binary Search Tree(BST) where the difference between heights of left and right subtrees cannot be more than one for all nodes.
>>[!info] C++
>>`map` `set` `multimap` `multiset` are all implemented by Balanced Search Tree.
>>That's why their insertion/deletion's time complexity if $O(logn)$
>>Remember `unordered_map` `unordered_set` are implemented by hash table

## Storage of Binary Tree

1. linked list
 ```cpp
 struct TreeNode
 {
 	int val;
 	struct TreeNode* left;
 	struct TreeNode* right;
 	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 }
 ```
 
2. Array
   say the index of a node is `i`:
   - the index of its left child is `i * 2 + 1`
   - the index of its right child is `i * 2 + 2` 

## Traversal of Binary Tree

### Depth-First Search(DFS)
Can be implemented in both *Recursion* or *Iteration* method
- Preorder Traversal(cur-left-right)
- Inorder  Traversal(left-cur-right)
- Postorder Traversal(left-right-cur) 
### Breadth-First Search(BFS)
Can only be implemented by iteration method
- Level order Traversal

>[!Tip]
>1. **Stack is a data structure for recursion**, so we can write recursion from stack code
>2. **BFS is usually done by Queue, since FIFO**

## How to write recursion

### 1. Determine the parameters and return type

### 2. Determine the termination conditions

### 3. Determine the logic of single-level recursion.

## DFS in Recursion
1. Parameter and return type: the parameters should be a pointer to a node and a reference of a vector that records the results
2. Termination condition: the passed-in node is `nullptr`
3. logic of single-level recursion: keep traversing on children nodes, while insert the `cur->val` at right order

### 144 Binary Tree Preorder Traversal

```cpp
void traversal(TreeNode* root, vector<int>& vec)
{
	if(root == nullptr) return;
	vec.push_back(root->val);
	traversal(root->left, vec);
	traversal(root->right, vec);    
}


vector<int> preorderTraversal(TreeNode* root) {
	vector<int> vec;
	traversal(root, vec);
	return vec;
}
```

### 145 Binary Tree Postorder Traversal

```cpp
void traversal(TreeNode* root, vector<int> & vec)
{
	if(root == nullptr) return;
	traversal(root->left, vec);
	traversal(root->right, vec);
	vec.push_back(root->val);
}

vector<int> postorderTraversal(TreeNode* root) {
	vector<int> vec;
	traversal(root, vec);
	return vec;
}
```

### 94 Binary Tree  Inorder Traversal

```cpp
void traversal(TreeNode* root, vector<int>& vec)
{
	if(root == nullptr) return;
	traversal(root->left, vec);
	vec.push_back(root->val);
	traversal(root->right, vec);
}

vector<int> inorderTraversal(TreeNode* root) {
	vector<int> vec;
	traversal(root, vec);
	return vec;
}
```


## DFS in Iteration

Using **Stack**, **FILO**.
### Preorder(cur-left-right)
> [!important] Preorder does us a huge favor, since we are visiting the middle node first and we output it first, so we only need to push right and left children
we should operate in following order, so that the *right child will be out of the stack later* than the left:

```cpp
st.push(root);
while(!st.empty())
{
	cur = st.top(); // get middle
	st.pop();
	vec.push_back(cur->val); // visit middle
	// .. insert cur->val to result
	if(right) push(right);   // right in deeper of stack
	if(left)  push(left);    // left in higher of the stack
}
```

### Inorder(left-cur-right)
>[!important] we are visiting middle first but can't output it, we have to push middle nodes in the stack and keep looking for the most left child:
>

```cpp
cur = root;
while(cur != nullptr || !st.empty())
{
	if(cur) //push middle and visit left
	{
		st.push(cur); // push every left we find until hit the nullptr
		cur = cur->left;
	}
	else // reach the most left node in a branch
	{
		// pop out its parent, in this situation -- a middle
		// which is also previous left
		cur = st.top();
		st.pop();
		vec.push_back(cur->val); // record result
		cur = cur -> right; // look for the most left in the right branch
	}
}
```

### Postorder(left-right-cur)

>[!Tip] 
>Preorder(cur-left-right) 
>--reverse left and right--> (cur-right-left) --reverse all-->(left-right-cur)

```cpp
st.push(root)
while(!st.empty())
{
	cur = st.top();
	st.pop();
	// vec.push...
	if(left) st.push(left);
	if(right) st.push(right);
}

reverse(vec...);
```

###  Iteration All-in-one
>[!Tip] Push the visited but not dealt middle node to the stack and append an extra `nullptr` as an indicator

#### Inorder

```cpp
st.push(root)
while(!st.empty())
{
	cur = st.top();
	st.pop();
	
	if(cur)
	{
		if(right) st.push(right); // right
		st.push(cur);             // middle
		st.push(nullptr);             // indicator of undealed middle
		if(left) st.push(left);   // left
	}
	else // meet indicator
	{
		cur = st.top(); // get acutual middle
		st.pop();

		vec.push_back(cur->val);
	}
}
```

#### Preorder

```cpp
st.push(root)
while(!st.empty())
{
	cur = st.top();
	st.pop();
	
	if(cur)
	{
		if(right) st.push(right); // right
		if(left) st.push(left);   // left
		st.push(cur);             // middle
		st.push(nullptr);             // indicator of undealed middle
	}
	else // meet indicator
	{
		cur = st.top(); // get acutual middle
		st.pop();

		vec.push_back(cur->val);
	}
}
```

#### Postorder

```cpp
st.push(root)
while(!st.empty())
{
	cur = st.top();
	st.pop();
	
	if(cur)
	{
		st.push(cur);             // middle
		st.push(nullptr);             // indicator of undealed middle
		if(right) st.push(right); // right
		if(left) st.push(left);   // left
	}
	else // meet indicator
	{
		cur = st.top(); // get acutual middle
		st.pop();

		vec.push_back(cur->val);
	}
}
```

## BFS -- level order (lc102)

### Iteration `queue`

```cpp
vector<vector<int>> levelOrderBy(TreeNode* root) {
	
	queue<TreeNode*> que;
	vector<vector<int>> vec;
	if(root)    que.push(root);

	// tmp value defines outside of loop for once to avoid duplicated
	// construction and destruction
	int levelSize = 0;
	TreeNode* cur;
	
	while(!que.empty())
	{
		// at the start of each level, retrieve the size of it
		levelSize = que.size();
		vector<int> levelVec(levelSize);
		
		// get all the children of current level at left to right order
		for(int i = 0; i < levelSize; ++i)
		{
			cur = que.front();
			que.pop();
			levelVec[i] = cur->val; // record cur val
			if(cur->left)   que.push(cur->left); // push left
			if(cur->right)  que.push(cur->right);// push right
		}

		// append cur level's vals to finnal results
		vec.push_back(levelVec);
	}
	return vec;
}
```

### Recursion

```cpp
void traversal(TreeNode* node, vector<vector<int>>& vec, int depth)
{
	if(!node)   return;

	if(depth == vec.size())
	{
		vec.push_back(vector<int>());
	}
	
	vec[depth].push_back(node->val);
	
	traversal(node->left, vec, depth + 1);
	traversal(node->right, vec, depth + 1);
}

vector<vector<int>> levelOrder(TreeNode* root) {
	vector<vector<int>> vec;
	traversal(root, vec, 0);
	return vec;
}
```

### 107 Binary Tree Level Order Traversal II

BFS + reverse vector at the end
	or push each level vector to the front of `vec.emplace(vec.begin(), move(levelVec));`

### 199 Binary Tree Right Side View
imagine yourself standing on the **right side** of it, return _the values of the nodes you can see ordered from top to bottom_.
**Example**:
![[6_Binary_Tree-20240729222641757.webp]]
	**Input:** root = [1,2,3,null,5,null,4]
	**Output:** [1,3,4]

>[!info] BFS + only record the most right of each level to the results
>To optimize the number of times of finding the most right of each level, we push the children from right to the left, the first of each level 'front()' is the most right one

```cpp
vector<int> rightSideView(TreeNode* root) {
	queue<TreeNode*> que;
	vector<int> vec;
	if(root)    que.push(root);
	while(!que.empty())
	{
		size_t levelSize = que.size();
		TreeNode* node = que.front();
		// the first of each level is the most right
		vec.emplace_back(node->val);
		while(levelSize-- > 0)
		{
			node = que.front();
			que.pop();
			// each level push right to left
			if(node->right) que.push(node->right);
			if(node->left) que.push(node->left);
		}
	}
	return vec;
}
```

### 637. Average of Levels in Binary Tree
Given the `root` of a binary tree, return _the average value of the nodes on each level in the form of an array_. Answers within `10-5` of the actual answer will be accepted.

>[!info] record sum and number of nodes for each level during recursion, and divide them in the end for calculating average

```cpp
void traversal(TreeNode* node, vector<pair<double, size_t>>& res, int depth)
{
	if(!node)   return;
	if(depth == res.size())
		res.emplace_back(0, 0);
	
	res[depth].first += node->val;
	++res[depth].second;

	traversal(node->left, res, depth + 1);
	traversal(node->right, res, depth + 1);
}

vector<double> averageOfLevels(TreeNode* root) {
	vector<pair<double, size_t>> info;
	traversal(root, info, 0);

	vector<double> res(info.size());
	for(int i = 0; i < info.size(); ++i)
	{
		res[i] = info[i].first / static_cast<double>(info[i].second);
	}
	return res;
}
```

### 429 N-ary Tree level Order Traversal

>[info] BFS + just replace push left and right to push every valid children

```cpp
vector<vector<int>> levelOrder(Node* root) {
	queue<Node*> que;
	vector<vector<int>> vec;
	if(root)    que.push(root);
	while(!que.empty())
	{
		size_t size = que.size();
		vector<int> levelVec(size);
		for(size_t i = 0; i < size; ++i)
		{
			Node* node = que.front();
			que.pop();
			levelVec[i] = node->val;
			for(auto& child : node->children)
			{
				if(child)
					que.push(child);
			}
		}
		vec.emplace_back(move(levelVec));
	}
	return vec;
}
```

### 515 Find Largest Value in Each Tree Row

```cpp
vector<int> largestValues(TreeNode* root) {
	queue<TreeNode*> que;
	vector<int> vec;
	if(root)    que.push(root);

	while(!que.empty())
	{
		size_t size = que.size();
		int maxValue = INT_MIN;

		for(size_t i = 0; i < size; ++i)
		{
			TreeNode* node = que.front();
			que.pop();
			maxValue = max(maxValue, node->val);
			if(node->left)  que.push(node->left);
			if(node->right)  que.push(node->right);
		}
		vec.emplace_back(maxValue);
	}
	return vec;
}
```

### 116 Populating Next Right Pointers in Each Node

>[!info] Same question as 117. Populating Next Right Pointers in Each Node II
>We don't care if the tree is perfect or not, we are breadth-first-searching anyway.

You are given a **perfect binary tree** where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:
```cpp
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to `NULL`.
Initially, all next pointers are set to `NULL`.

![[6_Binary_Tree-20240729231838838.webp]]

>[!tip] when iterating each level, after retrieving `cur` and pop it out, the new `que->front()` is our `cur->next`

```cpp
Node* connect(Node* root) {
	queue<Node*> que;
	if(root)    que.push(root);
	while(!que.empty())
	{
		int sz = que.size();
		while(sz-- > 0)
		{
			Node* cur = que.front();
			que.pop();
			if(cur->left)   que.push(cur->left);
			if(cur->right)  que.push(cur->right);
			
			if(sz == 0)
				cur->next = nullptr;
			else
				cur->next = que.front();
		}
	}

	return root;
}
```

### 104 Maximum Depth of Binary Tree
root at depth 1, get the max depth

```cpp
 void traversal(TreeNode* node, int& maxDepth, int depth)
    {
        if(!node)   return;
        if(maxDepth < depth)
            maxDepth = depth;
        traversal(node->left, maxDepth, depth + 1);
        traversal(node->right, maxDepth, depth + 1);
    }

    int maxDepth(TreeNode* root) {
        int maxDepth = 0;
        traversal(root, maxDepth, 1);
        return maxDepth;
    }
```

### 111 Minimum Depth of Binary Tree
The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

**Note:** A leaf is a node with no children. So when we reach the first leave, return its depth.

```cpp
int minDepth(TreeNode* root) {
	queue<TreeNode*> que;
	if(root)    que.push(root);
	int depth = 0;
	while(!que.empty())
	{
		++depth;
		size_t sz = que.size();
		while(sz-- > 0)
		{
			TreeNode* node = que.front();
			que.pop();

			if(!node->left && !node->right) return depth;
			if(node->left) que.push(node->left);
			if(node->right) que.push(node->right);
		}
	}

	return 0;
}
```