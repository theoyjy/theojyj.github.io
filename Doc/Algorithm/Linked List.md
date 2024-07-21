>[!Definition] Linked List is a linear structure linked by pointers. It consists of nodes where each node contains **data** and a **reference (link)** to the next node in the sequence. 
>
>This allows for dynamic memory allocation and efficient **insertion** and **deletion** operations compared to arrays.
>The entry node of the list is `head`

### Linked List Vs Arrays:

|                    | Array                                                  | Linked List                                                 |
| ------------------ | ------------------------------------------------------ | ----------------------------------------------------------- |
| Data Structure     | Contiguous                                             | Non-contiguous                                              |
| Memory Allocation  | Static                                                 | Dynamic                                                     |
| Insertion/Deletion | Inefficient O(n)                                       | Efficient O(1)                                              |
| Access             | Random O(1)                                            | Sequential O(n)                                             |
| Scenario           | data is constant, frequently access, rarely add/remove | data varies over time, frequently add/remove, rarely access |

### Types:
1. Singly Linked List
2. Doubly Linked List
3. Circular Linked List

### Class Definition

```cpp
struct ListNode
{
	int val; // data
	ListNode * next;
	ListNode(int x) : val(x), next(nullptr) {}
}
```



### dummy head node
>[!Important] 
>It's very helpful to declare a dummy head whose next points the head of original list, in this way, we can handle the situation when deleting the original head, the `dummyhead->next` is always the actual head.
>![[Linked List-20240719193708368.webp]]

### 203 Remove Linked List Elements
Given the `head` of a linked list and an integer `val`, remove all the nodes of the linked list that has `Node.val == val`, return the *new head*

```cpp
ListNode* removeElements(ListNode* head, int val) {
	ListNode* dummyHead = new ListNode(0, head);
	ListNode* cur = dummyHead;
	while(cur->next != nullptr)
	{
		if(cur->next->val == val)
		{
			ListNode* toRemove = cur->next;
			cur->next = cur->next->next;
			delete toRemove;
		}
		else
			cur = cur->next;
	}
	return dummyHead->next;
}
```

### 707 Design Linked List
Design your implementation of the linked list. Assume all nodes in the linked list are **0-indexed**.

Implement the `MyLinkedList` class:

- `MyLinkedList()` Initializes the `MyLinkedList` object.
- `int get(int index)` Get the value of the `indexth` node in the linked list. If the index is invalid, return `-1`.
- `void addAtHead(int val)` Add a node of value `val` before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
- `void addAtTail(int val)` Append a node of value `val` as the last element of the linked list.
- `void addAtIndex(int index, int val)` Add a node of value `val` before the `indexth` node in the linked list. If `index` equals the length of the linked list, the node will be appended to the end of the linked list. If `index` is greater than the length, the node **will not be inserted**.
- `void deleteAtIndex(int index)` Delete the `indexth` node in the linked list, if the index is valid.

#### Singly Linked List

>[!Caution] Using dummy head as a data member, please pay attention to **initialization of `cur`**:
> 1. when `addAtIndex(index)`, we want to do `cur->next = new ..`, suppose `index = 0`, the `cur` has to be `dummyHead`, so `ListNode* cur = dummy`
> 2. when `get(index)`, we wanna `return cur->value;`, when `index = 0`, the `cur` has to be at true head, so `ListNode* cur = dummyHead->next;`

```cpp
class MyLinkedList {
public:

    struct ListNode
    {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* nextNode) : val(x), next(nextNode) {}
    };

    MyLinkedList() : size(0) {
        dummyHead = new ListNode(0);
    }

    // index 0 refers to (dummyHead -> next)
    // so 0 <--> dummyHead->next
    int get(int index) {

        if(index > size - 1 || index < 0)    return -1;
        
        ListNode* cur =  dummyHead->next;
        while(index--)
        {
            cur = cur -> next;
        }
        return cur ? cur->val : -1;
    }

    void addAtHead(int val) {

        dummyHead->next = new ListNode(val, dummyHead->next);
        ++size;
    }

    void addAtTail(int val) {
        ListNode * cur = dummyHead;
        while(cur->next)
        {
            cur = cur->next;
        }
        cur->next = new ListNode(val);
        ++size;
    }

    // add at 0, cur has to be dummyHead to be able to assign the head
    // so 0 <--> dummyHead
    void addAtIndex(int index, int val) {
        if(index > size)    return;
        
        ListNode * cur = dummyHead;
        while(index--)
        {
            cur = cur->next;
        }
        ListNode* next = cur->next;
        cur->next = new ListNode(val, next);
        ++size;
    }

    // to delete at 0, cur has to be at dummyHead
    // so 0 <--> dummyHead
    void deleteAtIndex(int index) {

        if(index > size - 1 || index < 0)
            return;

        ListNode* cur = dummyHead;
        while(index--)
        {
            cur = cur -> next;
        }
        ListNode* next = cur->next;
        cur->next = next->next;
        --size;
        delete next;
    }

private:
    ListNode* dummyHead;
    int size;
};
```

#### Doubly Linked List

```cpp
class MyLinkedList {
public:

    struct ListNode
    {
        int val;
        ListNode* next;
        ListNode* pre;
        ListNode(int x) : val(x), next(nullptr), pre(nullptr) {}
        ListNode(int x, ListNode* nextNode, ListNode* preNode) : val(x), next(nextNode), pre(preNode) {}
    };

    MyLinkedList() : size(0) {
        dummyHead = new ListNode(0);
    }

    // index 0 refers to (dummyHead -> next)
    // so 0 <--> dummyHead->next
    int get(int index) {
        if(index > size - 1 || index < 0)    return -1;
        ListNode* cur =  dummyHead->next;
        while(index--)
        {
            cur = cur -> next;
        }
        return cur ? cur->val : -1;
    }

    void addAtHead(int val) {
        ListNode* next = dummyHead->next;
        dummyHead->next = new ListNode(val, next, dummyHead);
        if(next)
            next->pre = dummyHead->next;
        ++size;
    }

    void addAtTail(int val) {
        ListNode * cur = dummyHead;
        while(cur->next)
        {
            cur = cur->next;
        }
        cur->next = new ListNode(val);
        cur->next->pre = cur;
        ++size;
    }

    // add at 0, cur has to be dummyHead to be able to assign the head
    // so 0 <--> dummyHead
    void addAtIndex(int index, int val) {
        if(index > size)    return;
        ListNode * cur = dummyHead;
        while(index--)
        {
            cur = cur->next;
        }
        ListNode* next = cur->next;
        cur->next = new ListNode(val, next, cur);
        if(next)
            next->pre = cur->next;
        ++size;
    }

    // to delete at 0, cur has to be at dummyHead
    // so 0 <--> dummyHead
    void deleteAtIndex(int index) {
        if(index > size - 1 || index < 0)
            return;
        ListNode* cur = dummyHead;
        while(index--)
        {
            cur = cur -> next;
        }
        ListNode* next = cur->next;
        cur->next = next->next;
        if(next->next)
        {
            next->next->pre = cur;
        }
        --size;
        delete next;
    }
private:
    ListNode* dummyHead;
    int size;
};
```


### 206 Reverse Linked List
Given the `head` of a singly linked list, reverse the list, and return _the reversed list_.

#### Method 1 dummy head
![[Linked List-20240719211242047.webp]]
```cpp
 ListNode* reverseList(ListNode* head) {
	ListNode* dummyHead = new ListNode(0);
	ListNode* cur = head;
	while(cur)
	{
		ListNode* newHead = cur;
		ListNode* newHeadNext = dummyHead->next;
		cur = cur->next;
		dummyHead->next = newHead;
		newHead->next = newHeadNext;
	}
	return dummyHead->next;
}
```

#### Method 2 Pre and Cur Pointer
Quite same as method 1
Reversing the linked list with new head moving from original head to tail 
```cpp
ListNode* reverseList(ListNode* head) {
	ListNode * pre = nullptr;
	ListNode * cur = head;
	ListNode * nextIter =  nullptr;
	while(cur)
	{
		nextIter = cur->next;
		cur->next = pre;
		pre = cur;
		cur = nextIter;
	}
	return pre;
}
```

#### Method 3 recursion with same idea from method 2
```cpp
ListNode* reverse(ListNode* pre,ListNode* cur){
	if(cur == NULL) return pre;
	ListNode* nextIter = cur->next;
	cur->next = pre;
	// same as method 2:
	// pre = cur;
	// cur = temp;
	return reverse(cur,temp);
}

ListNode* reverseList(ListNode* head)
{
	// same as method 2:
	// pre = nullptr
	// cur = head
	return reverse(nullptr, head);
}
```

#### Method 4 recursion from tail to head
1. Keeping looking for the tail which is the new head, returns for the first time,
2. `head->next->next = nullptr` because it's the new tail
3. Reversing the `head` and `head->next` 
![[Linked List-20240719212435943.webp|641]]
```cpp
ListNode* reverseList(ListNode* head) {
	// finding tail which is new head
	if(head == NULL) return NULL;
	if (head->next == NULL) return head;
	ListNode *newHead = reverseList(head->next);
	
	// imagine you have the newhead, reverse the last second
	head->next->next = head;
	// 此时的 head 节点为尾节点，next 需要指向 NULL
	head->next = NULL;
	return newHead;
}
```

Simulation of the recursion
![[Linked List-20240719212436125.webp]]


### 24 Swap Nodes in Pairs
Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

![[Linked List-20240721163754727.webp]]

```cpp
ListNode* swapPairs(ListNode* head) {

	if(!head || !head->next)    return head;
	ListNode* dummyHead = new ListNode(0, head);

	ListNode * cur = dummyHead;
	ListNode* Swap1Node;
	ListNode* NextPair;

	while(cur->next && cur->next->next)
	{
		Swap1Node = cur->next;
		NextPair = cur->next->next->next;
		cur->next = cur->next->next; // Swap2Node
		cur->next->next = Swap1Node;
		cur->next->next->next = NextPair;
		cur = Swap1Node;
	}
	return dummyHead->next;

}
```

## Dual Pointers Method in Linked List
### 19 Remove Nth Node From End of List -- fast and slow
Given the `head` of a linked list, remove the `nth` node from the end of the list and return its head.

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {

	ListNode* dummyHead = new ListNode(0, head);
	ListNode* slow = dummyHead;
	ListNode* fast = dummyHead;
	while(n-- > -1 && fast) // fast move one more, 
	{						//since slow has to be front of the last-nth
		fast = fast->next;
	}
	
	while(fast) // when fast gets to the tail, slow is at the front of
	{           // the last n-th node
		fast = fast->next;
		slow = slow->next;
	}
	
	ListNode* tmp = slow->next;
	slow->next = tmp->next;
	delete tmp;

	return dummyHead->next;

}
```

### 02.07 Intersection of Two Linked Lists LCCI
Given two (singly) linked lists, determine if the two lists intersect. Return the inter­secting node. Note that the intersection is defined based on reference, not value. That is, if the kth node of the first linked list is the exact same node (by reference) as the `jth` node of the second linked list, then they are intersecting.

```cpp
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

	// 1. get lengths of two lists
	int lenA = 0, lenB = 0;
	{
		ListNode* curA = headA;
		ListNode* curB = headB;
		while(curA)
		{
			++lenA;
			curA = curA->next;
		}

		while(curB)
		{
			++lenB;
			curB = curB->next;
		}
	}

	// 2. distinguish which list is longer
	ListNode* longer, * shorter;
	int diff = 0;
	if(lenA < lenB)
	{
		diff = lenB - lenA;
		longer = headB;
		shorter = headA;
	}
	else
	{
		diff = lenA - lenB;
		longer = headA;
		shorter = headB;
	}
	
	// 3. move longer pointer in the longer list, to make longer and shorter 
	// pointers at the same distance to tail
	while(diff-- && longer)
	{
		longer = longer->next;
	}

	// 4. move dual pointers together until they meet
	while(longer && shorter && longer != shorter)
	{
		longer = longer->next;
		shorter = shorter->next;
	}
	
	// 5. there might be no intersetion at all, so be careful when returning
	return longer == shorter ? longer : NULL;
}
```

### 142 Linked List Cycle II
Given the `head` of a linked list, return _the node where the cycle begins. If there is no cycle, return_ `null`.

**Do not modify** the linked list.
![[Linked List-20240721192115648.webp]]
```c
2 * (x + y) = x + n * (y + z) + y
x + y = n * (y + z)
x = (n - 1) * (y + z) + z // (y + z) is the length of circle.
```

```cpp
ListNode *detectCycle(ListNode *head) {
	ListNode* fast = head, *slow = head;
	while(fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow) // get to meeting point
		{
			break;
		}
	}

	if(!fast || !fast->next)    return NULL;

	fast = head;
	while(fast != slow) // x = z, so fast and slow will eventually meet at 
	{                   // the start of intersection
		fast = fast->next;
		slow = slow->next;
	}
	return fast;
}
```