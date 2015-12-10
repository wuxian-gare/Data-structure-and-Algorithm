/*
* Part of the questions here is from leetcode(https://leetcode.com/).
* 主要是二叉树的常见算法
*/

#include "head.h"	//my own head file
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x),left(NULL),right(NULL) {}  
};

class myTree{
public:
  /*
	*创建二叉树,用于方便程序测试
	*函数参数为一个包含节点数值的vector,返回创建成功之后的二叉树根节点
  *暂以val为0表示空节点，可自行更改
	*/
	TreeNode *createTree(vector<int> a){ //0表示空节点
		int size = a.size();
		vector <TreeNode *> res;
		TreeNode flag(0);
		res.push_back(&flag);
		int i = 0;
		for (i = 0; i < size; i++){
			if (a[i] == 0){
				res.push_back(NULL);
				continue;
			}
			TreeNode *temp=new TreeNode(a[i]);
			res.push_back(temp);
		}
		for (i = 1; i < size+1; i++){
			if (res[i] == NULL)
				continue;
			if (2 * i < size + 1){
				res[i]->left = res[2 * i];
			}
			if (2 * i < size){
				res[i]->right = res[2 * i+1];
			}
		}
		return res[1];
	}
	
	/*
	*二叉树三种遍历非递归实现
	*用栈实现
	*/

	/*
	*前序遍历（根->左->右）
	*/
	void preOrder(TreeNode *root){
		stack<TreeNode*> s;
		TreeNode *p = root;
		while (p != NULL || !s.empty()){
			while (p != NULL){
				cout << p->val << " ";
				s.push(p);
				p = p->left;
			}
			if (!s.empty()){
				p = s.top();
				s.pop();
				p = p->right;
			}
		}
		cout << endl;
	}

	/*
	*中序遍历（左->根->右）
	*/

	void inOrder(TreeNode *root)      //非递归中序遍历
	{
		stack<TreeNode*> s;
		TreeNode *p = root;
		while (p != NULL || !s.empty())
		{
			while (p != NULL)
			{
				s.push(p);
				p = p->left;
			}
			if (!s.empty())
			{
				p = s.top();
				cout << p->val << " ";
				s.pop();
				p = p->right;
			}
		}
		cout << endl;
	}

	/*
	* Leetcode #230：Kth Smallest Element in a BST
	* 基于上述中序遍历
	*/
	int kthSmallest(TreeNode* root, int k) {
		int count = 0;
		stack<TreeNode*> s;
		TreeNode *p = root;
		while (p != NULL || !s.empty())
		{
			while (p != NULL)
			{
				s.push(p);
				p = p->left;
			}
			if (!s.empty())
			{
				p = s.top();
				count++;
				if (count == k)			//在此比较是否是第K小
					return p->val;
				s.pop();
				p = p->right;
			}
		}
	}
	

	/*
	*后序遍历（左->右->根）
	*第一种思路：对于任一结点P，将其入栈，然后沿其左子树一直往下搜索，直到搜索到没有左孩子的结点，
	*此时该结点出现在栈顶，但是此时不能将其出栈并访问，因此其右孩子还为被访问。所以接下来按照相同的
	*规则对其右子树进行相同的处理，当访问完其右孩子时，该结点又出现在栈顶，此时可以将其出栈并访问。
	*这样就保证了正确的访问顺序。可以看出，在这个过程中，每个结点都两次出现在栈顶，只有在第二次出现在
	*栈顶时，才能访问它。因此需要多设置一个变量标识该结点是否是第一次出现在栈顶。
	*/

	void postOrder_1(TreeNode *root)    //非递归后序遍历
	{
		stack<TreeNode_temp*> s;
		TreeNode *p = root;
		TreeNode_temp *temp;
		while (p != NULL || !s.empty())
		{
			while (p != NULL)              //沿左子树一直往下搜索，直至出现没有左子树的结点 
			{
				TreeNode_temp *btn = (TreeNode_temp *)malloc(sizeof(TreeNode_temp));
				btn->BTNode = p;
				btn->isFirst = true;
				s.push(btn);
				p = p->left;
			}
			if (!s.empty())
			{
				temp = s.top();
				s.pop();
				if (temp->isFirst == true)     //表示是第一次出现在栈顶 
				{
					temp->isFirst = false;
					s.push(temp);
					p = temp->BTNode->right;
				}
				else                        //第二次出现在栈顶 
				{
					cout << temp->BTNode->val << " ";
					p = NULL;
				}
			}
		}
		cout << endl;
	}


	/*
	*第二种思路：要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，
	*先将其入栈。如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右
	*孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。若非上述两
	*种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子
	*在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
	*/
	void postOrder_2(TreeNode *root){
		stack<TreeNode*> s;
		TreeNode *cur;                      //当前结点 
		TreeNode *pre = NULL;                 //前一次访问的结点 
		s.push(root);
		while (!s.empty()){
			cur = s.top();
			if ((cur->left == NULL&&cur->right == NULL) ||
				(pre != NULL && (pre == cur->left || pre == cur->right))){
				cout << cur->val << " ";  //如果当前结点没有孩子结点或者孩子节点都已被访问过 
				s.pop();
				pre = cur;
			}
			else{
				if (cur->right != NULL)
					s.push(cur->right);
				if (cur->left != NULL)
					s.push(cur->left);
			}
		}
		cout << endl;
	}


	void postOrder_3(TreeNode *p){
		if (!p) 
			return;
		stack<pair<TreeNode*, int> > s;
		TreeNode *t;
		int unUsed;
		s.push(make_pair(p, 1));
		while (!s.empty()){
			t = s.top().first;
			unUsed = s.top().second;
			s.pop();
			if (unUsed){
				s.push(make_pair(t, 0));
				if (t->right)
					s.push(make_pair(t->right, 1));
				if (t->left)
					s.push(make_pair(t->left, 1));
			}
			else 
				printf("%d ", t->val);
		}
		cout << endl;
	}

	/*
	*morris中序遍历算法
	*/
	void morris_inorder_traversal(struct TreeNode *root){
		struct TreeNode *pre, *cur;
		if (root == NULL)
			return;
		cur = root;
		while (cur != NULL){
			if (cur->left == NULL){					//左子树为空
				cout << cur->val << " ";
				cur = cur->right;
			}
			else{
				pre = cur->left;					//找到cur的前驱节点
				while (pre->right != NULL&&pre->right != cur)
					pre = pre->right;				//找到最右叶子节点
				if (pre->right == NULL){				//第一次遍历到
					pre->right = cur;
					cur = cur->left;
				}
				else{									//第二次遍历到，恢复原有结构，修改right指针
					pre->right = NULL;
					cout << cur->val << " ";
					cur = cur->right;
				}
			}	
		} 
		cout << endl;
	}//end of morris_inorder_traversal

}
