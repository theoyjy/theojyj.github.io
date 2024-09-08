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
- **height**: number of *edges* to reach the root. The Height of longest leave is 1.
- **Level/Depth**: number of *nodes* to reach the root. level of root is *0 or 1*.

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
int maxDepth(TreeNode* root) {
	if(!node)   return 0;
	return max(maxDepth(node->left), maxDepth(node->right)) + 1;
}
```

### 111 Minimum Depth of Binary Tree
The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

**Note:** A leaf is a node with no children. So when we reach the first leave, return its depth.

#### Iteration

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

#### Recursion

```cpp
int minDepth(TreeNode* root) {
	if(!root)   return 0; // this is a leave
	
	if(!root->left && root->right) // not leave
		return 1 + minDepth(root->right);

	if(root->left && !root->right)
		return 1 + minDepth(root->left);

	return 1 + min(minDepth(root->left),  minDepth(root->right));  

}
```
## Operations on the BT

### 226 Invert Binary Tree
![[6_Binary_Tree-20240730182555131.webp]]

>[!caution]
>preordered and postordered traversal would both be fine, except the inordered. Since it will invert the left subtree first, then swap it to the right, then invert the right subtree
>which leads to original left subtree inverted twice while the original right isn't inverted at all.
> 
> However, we can invert the left subtree(original right subtree) again after swap in the inordered traversal LOL.

```cpp
void traversal(TreeNode* root)
{
	if(!root)   return;
	// preorder
	swap(root->left, root->right);
	traversal(root->left);
	traversal(root->right);

	// postorder
	swap(root->left, root->right);
	traversal(root->left);
	traversal(root->right);

	// inorder
	traversal(root->left);
	swap(root->left, root->right);
	traversal(root->left); // do the trick
}

TreeNode* invertTree(TreeNode* root) {
	traversal(root);
	return root;
}
```

### 101 Symmetric Tree
![[6_Binary_Tree-20240730184706878.webp]]
>[!caution] it's not checking every two children of a node as above question, it only compares the left subtree and right subtree of the root.
>Plus we are comparing:
>- the outside part: `left->left` to `right->right`
>- the inside part: `left->right` to `right->left`

```cpp
bool compare(TreeNode* left, TreeNode* right)
{
	if(!left && !right)  return true;
	
	else if((left && !right) || (!left && right) 
			|| (left->val != right->val)) 
		return false; 
	
	return compare(left->left, right->right) 
		&& compare(left->right, right->left);
}

bool isSymmetric(TreeNode* root) {
	return compare(root->left, root->right);
}
```

---

### 110 Balanced Binary Tree
Given a binary tree, determine if it is **height-balanced**.

```cpp
/*
 * return -1 when unbalanced
 * otherwise returns the actual Height of node
 */
int getHeight(TreeNode* node)
{
	if(!root)   return 0;
	int left = getHeight(node->left);
	int right = getHeight(node->right);

	if(abs(left - right) > 1 || left == -1 || right == -1)
		return -1;
	
	return max(left, right) + 1;
}

bool isBalanced(TreeNode* root) {
	return getHeight(root) > -1;
}
```


### 257 Binary Tree Paths
Given the `root` of a binary tree, return _all root-to-leaf paths in **any order**_.
#### recursion on a reference of an array 

```cpp
void traversal(TreeNode* cur, vector<int>& path, vector<string>& result)
{
	path.emplace_back(cur->val);
	cout << "insert " << cur->val << endl;
	// termination condition is checking whether it's a leave
	if(!cur->left && !cur->right)
	{
		string pathStr;
		for(int i = 0; i < path.size() - 1; ++i)
		{
			pathStr += to_string(path[i]);
			pathStr += "->";
		}
		pathStr += to_string(path.back());
		cout << pathStr << endl;
		result.emplace_back(move(pathStr));
		return;
	}

	// since termination won't check if cur is nullptr
	// we have to check if passed-in node is nullptr before calling
	if(cur->left)
	{
		traversal(cur->left, path, result); // recur
		path.pop_back();                     // retrace
	}

	if(cur->right)
	{
		traversal(cur->right, path, result); // recur
		path.pop_back();                      // retrace
	}
		
}

vector<string> binaryTreePaths(TreeNode* root) {

	// since termination won't check if cur is nullptr
	// we have to check if passed-in node is nullptr before calling
	if(!root)   return {};

	vector<string> res;
	vector<int> path;
	traversal(root, path, res);
	return res;
}
```

#### recursion on a string that is passed by copying value

>[!tip]
> Every traversal we pass the `path + "->"`  which won't modify value of `path` in cur function's stack, which just fulfill the requirement of retracing.
>>[!question] Why no pass-by-reference?
>>The issue is not only do we have to pop "->", we have to pop the number as well, whereas, the number of digits of the previous number is uncertain. Of course we can find last `find` the end iterator of the last second "->", but it just increases the complexity of the code.  

```cpp
void traversal(TreeNode* cur, string path, vector<string>& result)  
{  
    path += to_string(cur->val);  
    if(!cur->left && !cur->right)  
    {        result.emplace_back(path);  
        return;  
    }  
    
    if(cur->left)  
    {        
	    traversal(cur->left, path + "->", result); // recur  
    }  
  
    if(cur->right)  
    {        
	    traversal(cur->right, path + "->", result); // recur  
    }  
}  
  
  
vector<string> binaryTreePaths(TreeNode* root) {  
  
    // since termination won't check if cur is nullptr  
    // we have to check if passed-in node is nullptr before calling    if(!root)   return {};  
    vector<string> res;  
    string path;  
    traversal(root, path, res);  
    return res;  
}
```


### 404 Sum of Left Leaves
**Example**:
![[6_Binary_Tree-20240731155134624.webp|197]]
	**Output**: 9 + 15 = 24

```cpp
int sumOfLeftLeaves(TreeNode* root) {

	// at leave or null can not know if it's left leave so just return 0
	if(!root
	|| (!root->left && !root->right))   return 0;
	
	// cur node's left child is a left leave
	if(root->left && !root->left->left && !root->left->right)
	{
		return root->left->val + sumOfLeftLeaves(root->right);
	}    

	return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);    
}
```

### 222. Count Complete Tree Nodes

>[!tip] As the given tree must be a complete tree, so all the leaves must be a part of a small perfect tree.
>![[6_Binary_Tree-20240731162727866.webp]]
>This info can help us reduce the time of visiting every nodes, we can ignore the nodes inside the perfect BTs by just retrieving the depth and calculate it.


```cpp
// the tree must be a complete binary tree
int countNodes(TreeNode* root) {

	if(!root) return 0;
	
	// check if a tree starts from cur node is a perfect tree
	// if true, we can cut the time of visiting the nodes inside it
	{
		int leftDepth = 0;
		int rightDepth = 0;
		auto left = root->left;
		auto right = root->right;
		while(left)
		{
			++leftDepth;
			left = left->left;
		}
		while(right)
		{
			++rightDepth;
			right = right->right;
		}
	
		// cur subtree is a perfect binary tree
		// no need to traversal inside of it
		// just calculate its number of nodes right away
		if(leftDepth == rightDepth)
		{
			return (2 << leftDepth) - 1;
		}
	}
	
	// this subtree is not perfect
	// iterate its children and plus 1 for cur node.
	return countNodes(root->left) + countNodes(root->right) + 1;
}
```

---

### 513 Find Bottom Left Tree Value

#### Recursion and Retraction

```cpp
int maxDepth = -1;
int leftLeave = 0;


void traversal(TreeNode* node, int depth)
{
	if(!node)   return;
	traversal(node->left, depth + 1);
	if(depth > maxDepth) // keep find leftest leave
	{
		maxDepth = depth;
		leftLeave = node->val;
	}
	traversal(node->right, depth + 1);
}

int findBottomLeftValue(TreeNode* root) {
	traversal(root, 0);
	return leftLeave;
}
```

#### Iteration on level

```cpp
int findBottomLeftValue(TreeNode* root) {
	queue<TreeNode*> que;
	if(root)    que.push(root);
	int res = 0;
	while(!que.empty())
	{
		size_t sz = que.size();
		res = que.front()->val; // lefteast node at the front of each layer
		while(sz-- > 0)
		{
			auto node = que.front();
			que.pop();

			if(node->left) que.push(node->left);
			if(node->right) que.push(node->right);
		}

	}
	return res;
}
```

### 112 Path Sum
Given the `root` of a binary tree and an integer `targetSum`, return `true` if the tree has a **root-to-leaf** path such that adding up all the values along the path equals `targetSum`.

A **leaf** is a node with no children.

#### Recursion & Retraction
```cpp
bool traversal(TreeNode* node, int target)
{
	if(!node->left && !node->right)
		return node->val == target;
	
	if(node->left && traversal(node->left, target - node->val))
		return true;
	if(node->right && traversal(node->right, target - node->val))
		return true;

	return false;
}


bool hasPathSum(TreeNode* root, int targetSum) {
	if(root)
		return traversal(root, targetSum);
	return false;
}
```

#### DFS Iteration
We have to record the sum along we iterate to the deeper nodes, retraction is quite hard in this scenario, so we record the `pathSum` in the stack

```cpp
bool hasPathSum(TreeNode* root, int targetSum) {
	stack<pair<TreeNode*, int>> st;
	if(root)    st.push({root, 0});
	while(!st.empty())
	{
		auto [cur, pathSum] = st.top();
		st.pop();

		if(!cur->left && !cur->right && pathSum + cur->val == targetSum)
		{
				return true;
		}

		if(cur->left)
			st.push({cur->left, pathSum + cur->val});
		if(cur->right)
			st.push({cur->right, pathSum + cur->val});
	}
	return false;
}
```

### 113 Path Sum II
Given the `root` of a binary tree and an integer `targetSum`, return _all **root-to-leaf** paths where the sum of the node values in the path equals_ `targetSum`_. Each path should be returned as a list of the node **values**, not node references_.

A **root-to-leaf** path is a path starting from the root and ending at any leaf node. A **leaf** is a node with no children.

```cpp
void traversal(TreeNode* node, vector<int>& path, int target)
{
	// push every new node
	path.push_back(node->val);

	// leave node: satisfy the requirement or not
	// it has to return, no nullptr should be passed to traversal func
	if(!node->left && !node->right)
	{
		if(node->val == target)
		{
			result.push_back(path);
		}            
		return;
	}

	// traverse one more, pop one to retrace
	if(node->left)
	{
		traversal(node->left, path, target - node->val);
		path.pop_back();
	}

	if(node->right)
	{
		traversal(node->right, path, target - node->val);
		path.pop_back();
	}

}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
	result.clear();
	vector<int> path;
	if(root)
		traversal(root, path, targetSum);
	return result;
}
```


### 106. Construct Binary Tree from Inorder and Postorder Traversal

>[!tip] `root` is at the *end* of the `postorder`, and is the splitter of left subtree and right subtree in `inorder`  

```cpp
//  inorder:    left.........   root    right..........
//postorder:    left.........   right...........   root
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
	if(inorder.empty() || postorder.empty())  return nullptr;
	TreeNode * root = new TreeNode(postorder.back());
	vector<int>::iterator position = find(inorder.begin(), inorder.end(), postorder.back());

	int leftSize = position - inorder.begin();
	vector<int> inLeft(inorder.begin(), inorder.begin()+leftSize);
	vector<int> inRight(inorder.begin()+leftSize+1, inorder.end());

	vector<int> posLeft(postorder.begin(), postorder.begin()+leftSize);
	vector<int> postRight(postorder.begin()+leftSize, postorder.end()-1);

	root -> left = buildTree(inLeft, posLeft);
	root -> right = buildTree(inRight, postRight);
	return root;
}
```

### 654 Maximum Binary Tree
You are given an integer array `nums` with no duplicates. A **maximum binary tree** can be built recursively from `nums` using the following algorithm:

1. Create a root node whose value is the maximum value in `nums`.
2. Recursively build the left subtree on the **subarray prefix** to the **left** of the maximum value.
3. Recursively build the right subtree on the **subarray suffix** to the **right** of the maximum value.

Return _the **maximum binary tree** built from_ `nums`.

```cpp
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
	if(nums.empty())    return nullptr;
	//find maximum in the array and make it root
	vector<int>::iterator maxi = max_element(nums.begin(), nums.end());
	TreeNode * root = new TreeNode (*maxi);
	//split array to left and right, both do not include the max one
	vector<int> left(nums.begin(), maxi);
	vector<int> right(maxi+1, nums.end());
	//construct for left and right
	//connect root with its children
	root->left=constructMaximumBinaryTree(left);
	root->right=constructMaximumBinaryTree(right);

	return root;
}
```

### 617 Merge Two Binary Trees
You are given two binary trees `root1` and `root2`.

Imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not. You need to merge the two trees into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of the new tree.

Return _the merged tree_.

```cpp
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
	if(!root1)  return root2;
	if(!root2)  return root1;
	
	root1->val += root2->val;
	root1->left = mergeTrees(root1->left, root2->left);
	root1->right = mergeTrees(root1->right, root2->right);
	return root1;
}
```

## Binary Search Tree Focus
### 700 Search in Binary Search Tree

```cpp
TreeNode* searchBST(TreeNode* root, int val) {
	if(!root || root->val == val)   return root;

	if(val > root->val)
		return searchBST(root->right, val);
	
	return searchBST(root->left, val);
}
```

### 98 Validate Binary Search Tree
Given the `root` of a binary tree, _determine if it is a valid binary search tree (BST)_.
A **valid BST** is defined as follows:
- The left subtree of a node contains only nodes with keys **less than** the node's key.
- The right subtree of a node contains only nodes with keys **greater than** the node's key.
- Both the left and right subtrees must also be binary search trees.

>[!Tip] A valid BST must be an increasing array if we traversing the tree by PreOrder!

```cpp
class Solution {

public:

    bool isValidBST(TreeNode* root) {
        if(!root)   return true;
        bool bLeft = isValidBST(root->left);
        if(maxValue < root->val)
            maxValue = root->val;
        else
            return false;
        return bLeft && isValidBST(root->right);
    }

private:
    long long int maxValue = LONG_MIN;
};
```

### 530 Minimum Absolute Difference in BST
Given the `root` of a Binary Search Tree (BST), return _the minimum absolute difference between the values of any two different nodes in the tree_.

>[!tip] BST is sorted, just get the minimum gap between adjacent nodes

```cpp
class Solution {
public:

    void traversal(TreeNode* node)
    {
        if(!node) return;
        traversal(node->left);
        if(pre)
        {
            result = min(result, abs(node->val - pre->val));
        }
        pre = node;
        traversal(node->right);
    }

    int getMinimumDifference(TreeNode* root) {
        traversal(root);
        return result;
    }
private:
    int result = INT_MAX;
    TreeNode* pre = NULL;
};
```


### 501 Find Mode in BST
Given the `root` of a binary search tree (BST) with duplicates, return _all the [mode(s)](https://en.wikipedia.org/wiki/Mode_(statistics)) (i.e., the most frequently occurred element) in it_.

```cpp
class Solution {
public:

    void traversal(TreeNode* node)
    {
        if(!node)   return;
        traversal(node->left);

        //update count and pre
        if(!pre)
            count = 1;
        else if(pre->val != node->val)
            count = 1;
        else
            ++count;
            
        pre = node;
        
        // updating result and maxFrequency accords to cur records
        if(count > maxFrequency)
        {
            maxFrequency = count;
            result.clear();
            result.emplace_back(pre->val);
        }
        else if(count == maxFrequency)
        {
            result.emplace_back(pre->val);
        }

        traversal(node->right);
    }

    vector<int> findMode(TreeNode* root) {
        if(!root)   return {};
        traversal(root);
        return result;
    }

private:
    TreeNode* pre = nullptr;
    int maxFrequency = 0;
    int count = 0;
    vector<int> result;
};
```


### 236 Lowest Common Ancestor of a Binary Tree
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the [definition of LCA on Wikipedia](https://en.wikipedia.org/wiki/Lowest_common_ancestor): “The lowest common ancestor is defined between two nodes `p` and `q` as the lowest node in `T` that has both `p` and `q` as descendants (where we allow **a node to be a descendant of itself**).”

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if(!root || root == p || root == q) // reach node, return it directly
		return root;
	auto left = lowestCommonAncestor(root->left, p, q);
	auto right = lowestCommonAncestor(root->right, p, q);
	if(left && right) 
	{
		// no need for `left!=right` since it just won't happen 
		// when they are both existed while equal
		return root;
	}
	
	if(left)
		return left;
	
	// right is either with value or nullptr
	return right;
}
```

### 235 Lowest Common Ancestor of a Binary **Search** Tree
Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

>[!hint] BST is sorted, so if root is smaller than both p and q, go to check the right child...

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if(!root)
		return root;

	if(root->val < p->val && root->val < q->val)
	{
		if(auto right = lowestCommonAncestor(root->right, p, q))
		{
			return right;
		}
	}

	if(root->val > p->val && root->val > q->val)
	{
		if(auto left = lowestCommonAncestor(root->left, p, q))
		{
			return left;
		}
	}

	return root;
}
```

### 701 Insert into a Binary Search Tree
You are given the `root` node of a binary search tree (BST) and a `value` to insert into the tree. Return _the root node of the BST after the insertion_. It is **guaranteed** that the new value does not exist in the original BST.

**Notice** that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return **any of them**.

>[!hint] No requiring the perfect position in this question, so we just insert it when we find the first satisfied NULL node. 

```cpp
TreeNode* insertIntoBST(TreeNode* root, int val) {
	if(!root) // reach a valid node, insert and return it
	{
		root = new TreeNode(val);
		return root;
	}
	
	if(root->val > val) // insert the val to the left
	{
		root->left = insertIntoBST(root->left, val);
	}
	else if(root->val < val) // insert the val to the right
	{
		root->right = insertIntoBST(root->right, val);
	}
	
	return root;
}
```

### 450 Delete Node in a BST
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return _the **root node reference** (possibly updated) of the BST_.

Basically, the deletion can be divided into two stages:

1. Search for a node to remove.
2. If the node is found, delete the node.

```cpp
TreeNode* deleteNode(TreeNode* root, int key) {
	if(!root)
		return root;
		
	// searching for the nodes
	if(root->val < key)
	{
		root->right = deleteNode(root->right, key);
		return root;
	}
	else if(root->val > key)
	{
		root->left = deleteNode(root->left, key);
		return root;
	}

	// find it
	auto left = root->left;
	auto right = root->right;
	// delete the node
	delete root;

	// the node has no child, easiest situation, return nullptr
	if(!left && !right)
	{
		return nullptr;
	}

	// only has one child, return that one to put it in the position
	// of the deleted one
	if(!left)
	{
		return right;
	}

	if(!right)
	{
		return left;
	}

	// has both children, place the whole left subtree to the
	// leftest leave of the right substree
	auto leftestLeafAtRight = right;
	while(leftestLeafAtRight->left)
	{
		leftestLeafAtRight = leftestLeafAtRight->left;
	}
	leftestLeafAtRight->left = left;
	return right;
}
```

### 669 Trim a BST

Given the `root` of a BST and the lowest and highest boundaries as `low` and `high`, trim tree so that all the elements lies in `[low, high]`.  Trimming the tree should **not** change the relative structure of the elements that will remain in the tree (i.e., any node's descendant should remain a descendant). It can be proven that there is a **unique answer**.

>[!caution] cur node outside the boundaries doesn't mean its children definitely are outside the boundaries. 

```cpp
TreeNode* trimBST(TreeNode* root, int low, int high) {
	if(!root)
		return root;
	
	if(root->val < low)
		return trimBST(root->right, low, high);
	
	if(root->val > high)
		return trimBST(root->left, low, high);
	
	root->left = trimBST(root->left, low, high);
	root->right = trimBST(root->right, low, high);
	return root;
}
```

### 108 Convert Sorted Array to Binary Search Tree
Given an integer array `nums` where the elements are sorted in **ascending order**, convert _it to a_ **_height-balanced_**  _binary search tree_.
 
```cpp
TreeNode* traversal(vector<int>& nums, int left, int right) {
	if (left > right) return nullptr;
	int mid = left + ((right - left) / 2);
	TreeNode* root = new TreeNode(nums[mid]);
	root->left = traversal(nums, left, mid - 1);
	root->right = traversal(nums, mid + 1, right);
	return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
	TreeNode* root = traversal(nums, 0, nums.size() - 1);
	return root;
}
```

### 538 Convert BST to Greater Tree

Given the `root` of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.

```cpp
class Solution {
private:
    int sum = 0;

    void traversal(TreeNode* root)
    {
        if(!root)
            return;
        
        traversal(root->right); // update sum from the largest value
        
        root->val += sum;
        sum = root->val;

        traversal(root->left);
    }

public:
    TreeNode* convertBST(TreeNode* root) {
        traversal(root);
        return root;
    }
};
```