/*
* List相关算法
*/

#include "head.h"
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
};

class myList{
public:
    /*
    *递归判断单链表是否是回文
    */
    bool isPalindrome(struct ListNode* head) {
        struct ListNode *start;
        if(head == NULL)
            return 1;
        start = head;
        return check(&start,head);
    }
    
    bool check(struct ListNode** point_1,struct ListNode* point_2)
    {
        if(point_2 == NULL)
            return 1;
        if(!check(point_1,point_2->next))
            return 0;
        if((*point_1)->val == point_2->val)
        {
            *point_1 = (*point_1)->next;
            return 1;
        }
        return 0;
    }
    
    /*
    *找出两个单链表的公共交点
    *解题思路:
    *1.首先想到的是哈希，先将一个链表中结点都插入字典中，然后遍历另一个链表中的结点看是否有结点在字典中;但这种方法需要开辟较大的内存空间来存储字典；
    *2.双指针法.首先对其中一个链表头尾连接.那么问题就变成了看另一个链表是否存在环的问题了.但这种方法改变了原本链表的结构，需要在最后对其还原；
    *3.先计算两个链表的长度差，然后对长链表头结点开始移动长度差长的结点,找到位置对应的结点.然后逐个比较是否相等;
    *http://www.2cto.com/kf/201502/374789.html
    */

    ListNode *getIntersectionNode(ListNode *headA,ListNode *headB) {
        if(headA == NULL || headB == NULL)
            return NULL;
        ListNode *p1 = headA,*p2 = headB;
        int size_A = 1,size_B = 1;
        int i = 0;
        while(p1->next != NULL)
        {
            size_A++;
            p1 = p1->next;
        }
        while(p2->next != NULL)
        {
            size_B++;
            p2 = p2->next;
        }
        if(p1 != p2)
            return NULL;
        if(size_A>size_B)
        {
            for(i = 0;i<size_A - size_B;i++)
                headA = headA->next;
        }
        else
        {
            for(i = 0;i<size_B - size_A;i++)
                headB = headB->next;
        }
        while(headA != headB)
        {
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }

    /*
    * 反转单链表
    *
	* 第一种方法：反转单链表. 分别用3个指针，指向前一个，当前，下一个 
	*/
	static void reverse(struct ListNode** head_ref){
			struct ListNode* prev = NULL;
			struct ListNode* current = *head_ref;
			struct ListNode* next;
		while (current != NULL)
		{
				next = current->next;
				current->next = prev;
				prev = current;
				current = next;
		}
			* head_ref = prev;
	}

	/* 
	* 使用递归的方法反转链表 
	*/
	static struct ListNode* reverseRecall(struct ListNode* head){
					//最后一个节点会返回 作为头部
		if (NULL == head || head->next == NULL) return head;
					//head->next 表示剩下的部分
		struct ListNode * newHead = reverseRecall(head->next);
		head->next->next = head; //颠倒指针
		head->next = NULL;//原来的头节点 next 应该为空
		return newHead;
	}

	/*
	*链表排序
	*1、归并排序
	*/

	ListNode* sortList(ListNode *head) {
		if (head == NULL || head->next == NULL) 
			return head;
		ListNode *slow = head;
		ListNode *fast = head;
			//用快慢指针找到中间节点
		while (fast->next != NULL && fast->next->next != NULL){
				slow = slow->next;
				fast = fast->next->next;
		}
			ListNode* list2 = slow->next;
			slow->next = NULL;
			head = sortList(head);
			list2 = sortList(list2);
			return merge(head, list2);
	}
    
    /*
    * 合并两个排序链表
    */
	ListNode* merge(ListNode* list1, ListNode* list2) {
		if (list1 == NULL) return list2;
		if (list2 == NULL) return list1;
				ListNode newHead;//链表头不存储实际数据
				ListNode* last = &newHead;
				//连接每个节点，只更换指针，因此空间复杂度为O(1)
		while (list1 != NULL && list2 != NULL){
			if (list1->val < list2->val){
						last->next = list1;
						list1 = list1->next;
				}
			else{
						last->next = list2;
						list2 = list2->next;
			}
					last = last->next;
		}
				//最后剩余的部分，直接连接起来即可
		if (list1 != NULL) 
				last->next = list1;
		else if (list2 != NULL) 
				last->next = list2;
		return newHead.next;
	}

	/*
	* Leetcode #24:	Swap Nodes in Pairs
	* Given a linked list, swap every two adjacent nodes and return its head.

	* For example,
	* Given 1->2->3->4, you should return the list as 2->1->4->3
	*/
	ListNode* swapPairs(ListNode* head) {
		ListNode *start = head;
		int temp = 0;
		while (start&&start->next){
			temp = start->val;
			start->val = start->next->val;
			start->next->val = temp;
			start = start->next->next;
		}
		return head;
	}

	/*
	* Leetcode #142：	找出循环链表的起始点
	*
	* 假设非循环长度为a,循环长度为b
	* 先用快慢指针，当快慢指针相遇时，假设过去i秒，则（2i-i）%b==0，即i%b==0
	* 这时候启动里一个指针，一次前进一步，a秒之后，则该指针走了a步，慢指针i+a步，相差(i+a-a)==i步，
	* 由于i%b==0，则一定在循环起始点相遇，此时返回
	*
	* 1. 环的长度是多少？
	*
	* 2. 如何找到环中第一个节点（即Linked List Cycle II）？
	*
	* 3. 如何将有环的链表变成单链表（解除环）？
	*
	* 4. 如何判断两个单链表是否有交点？如何找到第一个相交的节点？
	*http://blog.sina.com.cn/s/blog_6f611c300101fs1l.html
	*--------------------------------------------------------------------------------------
	*
	* 1. 方法一（网上都是这个答案）：
	*
	* 第一次相遇后，让slow,fast继续走，记录到下次相遇时循环了几次。因为当fast第二次到达Z点时，
	* fast走了一圈，slow走了半圈，而当fast第三次到达Z点时，fast走了两圈，slow走了一圈，正好还在Z点相遇。
	*
	* 方法二：
	*
	* 第一次相遇后，让fast停着不走了，slow继续走，记录到下次相遇时循环了几次。
	*
	* 方法三（最简单）：
	*
	* 第一次相遇时slow走过的距离：a+b，fast走过的距离：a+b+c+b。
	* 因为fast的速度是slow的两倍，所以fast走的距离是slow的两倍，有 2(a+b) = a+b+c+b，
	* 可以得到a=c（这个结论很重要！）。
	*
	* 我们发现L=b+c=a+b，也就是说，从一开始到二者第一次相遇，循环的次数就等于环的长度。
	*
	* 2. 我们已经得到了结论a=c，那么让两个指针分别从X和Z开始走，每次走一步，那么正好会在Y相遇！
	* 也就是环的第一个节点。
	*
	* 3. 在上一个问题的最后，将c段中Y点之前的那个节点与Y的链接切断即可。
	*
	* 4. 如何判断两个单链表是否有交点？先判断两个链表是否有环，如果一个有环一个没环，肯定不相交；
	* 如果两个都没有环，判断两个列表的尾部是否相等；如果两个都有环，判断一个链表上的Z点是否在另一个链表上。
	*/
	ListNode *detectCycle(ListNode *head) {
		if (NULL == head || head->next == NULL)
			return NULL;
		ListNode *fast = head;
		ListNode *slow = head;
		ListNode *res = head;
		int flag = 0;
		do{
			fast = fast->next->next;
			slow = slow->next;
			//快慢指针相遇之后置位，启动res指针
			if (fast == slow){
				flag = 1;
			}
			if (slow == res)			//此时一定在起始点
				return res;
			if (flag == 1){
				res = res->next;
			}
		} while (fast != NULL&&fast->next != NULL);
		return NULL;
	}
}
