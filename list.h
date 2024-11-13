#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

#if 0
//160 相交链表
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    unordered_set<ListNode *> mySet;
    ListNode *p = headA;
    while (p)
    {
        mySet.insert(p);
        p = p->next;
    }
    p = headB;
    while (p)
    {
        if (mySet.find(p) != mySet.end())
        {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}
#endif

#if 0
ListNode *myReverse(ListNode *head)
{
    if (head == nullptr)
        return nullptr;
    if (head->next == nullptr)
        return head;
    ListNode *ret = myReverse(head->next);
    head->next->next = head;
    head->next = nullptr;
    return ret;
}
//206 反转链表
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *cur = head;
    while (cur)
    {
        ListNode *nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}
#endif

#if 0
// 234 回文链表
bool isPalindrome(ListNode *head)
{
    ListNode *slow = head, *fast = head;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    //奇数
    if(fast){
        slow = slow->next;
    }
    //slow此时位于后半段链表
    //反转链表
    ListNode* prev = nullptr;
    ListNode* cur = slow;
    while(cur){
        ListNode* nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    //此时prev位于起始位置
    ListNode* p = head;
    while(prev){
        if(p->val != prev->val){
            return false;
        }
        p = p->next;
        prev = prev->next;
    }
    return true;
}
#endif

#if 0
//141 环形链表
bool hasCycle(ListNode *head) {
    if(head == nullptr) return false;
    ListNode* slow = head, *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            return true;
        }
    }
    return false;
}
#endif

// 21 合并两个有序链表
ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    ListNode *p = list1, *q = list2;
    ListNode *list3 = new ListNode(0), *k = list3;
    while (p && q)
    {
        if (p->val < q->val)
        {

            ListNode *newNode = new ListNode(p->val);
            k->next = newNode;
            k = k->next;
            p = p->next;
        }
        else
        {
            ListNode *newNode = new ListNode(q->val);
            k->next = newNode;
            k = k->next;
            q = q->next;
        }
    }
    if (p)
    {
        k->next = p;
    }
    if (q)
    {
        k->next = q;
    }
    return list3->next;
}

#if 0
//23 合并K个升序链表
struct Comp{
    bool operator()(ListNode* a, ListNode* b){
        return a->val > b->val;
    }
};
priority_queue<ListNode *, vector<ListNode *>, Comp> pq;
ListNode *mergeKLists(vector<ListNode *> &lists)
{
    for(ListNode* l : lists){
        if(l){
            pq.push(l);
        }
    }
    ListNode* head = new ListNode(0);
    ListNode* tail = head;
    while(!pq.empty()){
        ListNode* temp = pq.top();
        pq.pop();
        tail->next = temp;
        tail = temp;
        if(temp->next) pq.push(temp->next);
    }
    return head->next;
}
#endif

#if 0
// 2 两数之和
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    ListNode *l3 = new ListNode(0);
    ListNode *k = l3;
    int carry = 0;
    while (l1 || l2 || carry)
    {
        int sum = carry;
        if (l1)
        {
            sum += l1->val;
            l1=l1->next;
        }
        if (l2)
        {
            sum += l2->val;
            l2=l2->next;
        }
        ListNode *newNode = new ListNode(sum % 10);
        carry = sum / 10;
        k->next = newNode;
        k = k->next;
    }
    return l3->next;
}
#endif

// 19 删除链表倒数第N个节点
ListNode *removeNthFromEnd(ListNode *head, int n)
{
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *p = dummy, *q = dummy;
    // p位于n号位置
    while (n--)
    {
        p = p->next;
    }
    while (p->next)
    {
        p = p->next;
        q = q->next;
    }
    // 此时q位于n-1
    ListNode *del = q->next;
    q->next = del->next;
    delete del;
    return dummy->next;
}

// 24 两两交换链表中的节点
ListNode *swapPairs(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    ListNode *nxt = head->next;
    ListNode *nxtnxt = swapPairs(nxt->next);
    head->next = nxtnxt;
    nxt->next = head;
    return nxt;
}

// 25 k个一组翻转链表
pair<ListNode *, ListNode *> myReverse(ListNode *start, ListNode *end)
{
    ListNode *prev = nullptr;
    ListNode *cur = start;
    ListNode *next = end->next;
    while (cur != next)
    {
        ListNode *nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return {end, start};
}

ListNode *reverseKGroup(ListNode *head, int k)
{
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *prev = dummy;
    while (head)
    {
        // 找到第k个
        ListNode *tail = prev;
        for (int i = 0; i < k; i++)
        {
            tail = tail->next;
            if (!tail)
            {
                return dummy->next;
            }
        }

        // 反转
        ListNode *next = tail->next; // 记录下一组第一个
        pair<ListNode *, ListNode *> result = myReverse(head, tail);
        head = result.first;
        tail = result.second;

        // 连接前后
        prev->next = head;
        tail->next = next;

        head = next;
        prev = tail;
    }
    return dummy->next;
}

ListNode *reverseKGroup(ListNode *head, int k)
{
    if (head == nullptr)
        return head;
    int i = 1;
    ListNode *tail = head;
    while (tail != nullptr && tail->next != nullptr && i < k)
    {
        tail = tail->next;
        i++;
    }
    if (i < k) // tail==nullptr or tail->next==nullptr
        return head;

    ListNode *prev = nullptr;
    ListNode *cur = head;
    ListNode *next = tail->next;
    while (cur != next)
    {
        ListNode *nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    head->next = reverseKGroup(next, k);
    return tail;
}

#if 0
ListNode *reverseKGroup(ListNode *head, int k)
{
    if(head==nullptr) return head;
	int i = 1;
	//找最后一个节点
	ListNode* tail = head;
	//下面要用到tail->next, 我们这个尾巴节点一定是要有的
	while(tail!=nullptr && tail->next!= nullptr && i < k){
			tail = tail->next;
			i++;
	}
	if(i < k) return head;
	ListNode* prev = nullptr;
	ListNode* cur = head;
	ListNode* next = tail->next;
	//反转
	while(cur!=next){
		ListNode* nxt = cur->next;
		cur->next = prev;
		prev = cur;
		cur = nxt;
	}
	//接上下一个,此时head是最后的节点
	head->next = reverseKGroup(next, k);
	return tail;//返回第一个节点
}
#endif

Node *copyRandomList(Node *head)
{
    unordered_map<Node *, Node *> hash;
    Node *start = head;
    while (start)
    {
        Node *node = new Node(start->val);
        hash[start] = node;
        start = start->next;
    }

    start = head;
    while (start)
    {
        Node *node = hash[start];
        if (start->next)
            node->next = hash[start->next];
        if (start->random)
            node->random = hash[start->random];
        start = start->next;
    }
    return hash[head];
}

// 148 排序链表
ListNode *sortList(ListNode *head)
{
    ListNode *temp = head;
    vector<int> arr;
    while (temp)
    {
        arr.push_back(temp->val);
        temp = temp->next;
    }
    sort(arr.begin(), arr.end());
    temp = head;
    for (int i = 0; i < arr.size(); i++)
    {
        temp->val = arr[i];
        temp = temp->next;
    }
    return head;
}

// 146 LRU 缓存
struct DLinkedNode
{
    int key, value;
    DLinkedNode *prev, *next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr) {}
};
class LRUCache
{
public:
    LRUCache(int _capacity)
    {
        size = 0;
        capacity = _capacity;
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        if (!cache.count(key))
        {
            return -1;
        }
        DLinkedNode *node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value)
    {
        if (!cache.count(key))
        {
            DLinkedNode *node = new DLinkedNode(key, value);
            cache[key] = node;
            addToHead(node);
            ++size;
            if (size > capacity)
            {
                DLinkedNode *rm = removeTail();
                cache.erase(rm->key);
                delete rm;
                --size;
            }
        }
        else
        {
            cache[key]->value = value;
            moveToHead(cache[key]);
        }
    }

    void addToHead(DLinkedNode *node)
    {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(DLinkedNode *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode *node)
    {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode *removeTail()
    {
        DLinkedNode *node = tail->prev;
        removeNode(node);
        return node;
    }

private:
    DLinkedNode *head;
    DLinkedNode *tail;
    unordered_map<int, DLinkedNode *> cache;
    int size;
    int capacity;
};