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


