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

	/*
	*后序遍历3
	*/
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
	
	/*
	*给定一棵树，同时给出树中的两个结点(n1和n2)，求它们的最低公共祖先。
	*也就是常见的LCA(Lowest Common Ancestor )问题。
	*/
	//找到从root到 节点值为key的路径,存储在path中。没有的话返回-1
	bool findpath(TreeNode * root, vector<int> &path, int key){
		if (root == NULL) 
			return false;
		path.push_back(root->val);
		if (root->val == key) 
			return true;
				//左子树或右子树 是否找到,找到的话当前节点就在路径中了
		bool find = (findpath(root->left, path, key) || findpath(root->right, path, key));
		if (find) 
			return true;
				//该节点下未找到就弹出
		path.pop_back();
		return false;
	}

	int findLCA(TreeNode * root, int key1, int key2){			//比较两条路径的最后一个相同节点
		vector<int> path1, path2;
		bool find1 = findpath(root, path1, key1);
		bool find2 = findpath(root, path2, key2);
		if (find1 && find2){
			int ans;
			for (int i = 0; i<path1.size(); i++){
				if (path1[i] != path2[i]){
						break;
				}
				else
					ans = path1[i];
			}
			return ans;
		}
		return -1;
	}

	/*
	*更为简便的LCA算法
	*从root开始遍历，如果n1和n2中的任一个和root匹配，那么root就是LCA。 
	*如果都不匹配，则分别递归左、右子树，如果有一个 key（n1或n2）出现在左子树，
	*并且另一个key(n1或n2)出现在右子树，则root就是LCA.  如果两个key都出现在左
	*子树，则说明LCA在左子树中，否则在右子树。
	*/
	/*
	*时间复杂度为O(n)，但是此方法还是有所局限的，必须保证两个要查找的节点n1和n2都出现在树中。
	*如果n1不在树中，则会返回n2为LCA，理想答案应该为NULL。要解决这个问题，可以先查找下 n1和n2是否
	*出现在树中，然后加几个判断即可。
	*/
	struct TreeNode *findLCA2(struct TreeNode* root, int n1, int n2){
		if (root == NULL) return NULL;
			// 只要n1 或 n2 的任一个匹配即可
			//  (注意：如果 一个节点是另一个祖先，则返回的是祖先节点。因为递归是要返回到祖先的 )
		if (root->val == n1 || root->val == n2)
			return root;
			// 分别在左右子树查找
		TreeNode *left_lca = findLCA2(root->left, n1, n2);
		TreeNode *right_lca = findLCA2(root->right, n1, n2);
			// 如果都返回非空指针 Non-NULL, 则说明两个节点分别出现了在两个子树中，则当前节点肯定为LCA
		if (left_lca && right_lca)  
			return root;
			// 如果一个为空，在说明LCA在另一个子树
		return (left_lca != NULL) ? left_lca : right_lca;
	}

	/*
	* Leetcode #96:	Unique Binary Search Trees
	* Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
	*/
	int numTrees(int n) {
		if (n<1)
			return 0;
		int pre, next;
		int sum;
		vector<int> res;
		res.push_back(1);
		res.push_back(1);
		res.push_back(2);
		for (int i = 3; i <= n; i++){
			sum = 0;
			for (int j = 1; j <= i; j++){
				pre = j - 1;
				next = i - j;
				sum += res[pre] * res[next];
			}
			res.push_back(sum);
		}
		return res[n];

	}

	/*
	* Leetcode #108:	Convert Sorted Array to Binary Search Tree
	*/
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		if (nums.size() == 0)
			return NULL;
		int mid = nums.size() / 2;
		TreeNode *root = new TreeNode(nums[mid]);
		cout << "Node is :" << nums[mid] << endl;
		if (mid == 0){
			root->left = NULL;
			root->right = NULL;
			return root;
		}
		vector<int> left;
		vector<int> right;
		left.insert(left.begin(), nums.begin(), nums.begin() + mid);
		right.insert(right.begin(), nums.begin() + mid + 1, nums.end());
		root->left = sortedArrayToBST(left);
		root->right = sortedArrayToBST(right);
		return root;
	}

	void flatten(TreeNode* root) {
		if (root == NULL)
			return;
		TreeNode *start = root;
		TreeNode *temp;
		while (1){
			if (start->left != NULL&&start->right != NULL){
				temp = start->left;
				while (temp->right != NULL)
					temp = temp->right;
				temp->right = start->right;
				start->right = start->left;
				start->left = NULL;
				start = start->right;
			}
			else if (start->left != NULL&&start->right == NULL){
				start->right = start->left;
				start->left = NULL;
				start = start->right;
			}
			else if (start->left == NULL&&start->right != NULL){
				start = start->right;
			}
			else{
				break;
			}
		}
	}

	/*
	* Leetcode #111: Minimum Depth of Binary Tree
	* Given a binary tree, find its minimum depth.
	*
	* The minimum depth is the number of nodes along the shortest path from
	* the root node down to the nearest leaf node.
	*/
	int minDepth(TreeNode* root) {
		if (root == NULL)
			return 0;
		if (root->left == NULL&&root->right == NULL)			//叶子节点
			return 1;
		if (root->left != NULL&&root->right == NULL)			//只有右子树
			return minDepth(root->left) + 1;
		if (root->left == NULL&&root->right != NULL)			//只有左子树
			return minDepth(root->right) + 1;
		return min(minDepth(root->left), minDepth(root->right)) + 1;
	}

	/*
	* Leetcode #129：Sum Root to Leaf Numbers
	* 将从root到所有叶子节点的序列组成数累加起来
	* 使用了递归
	*/
	int sumNumbers(TreeNode* root) {
		if (root == NULL)
			return 0;
		int res = 0;
		int sum = 0;
		addToLeaf(root, res, sum);
		return res;
	}
	void addToLeaf(TreeNode *root, int &res, int sum){
		if (NULL == root)
			return;
		if (NULL == root->left&&NULL == root->right){
			res += (sum * 10 + root->val);
			return;
		}
		else{
			sum = sum * 10 + root->val;
			addToLeaf(root->left, res, sum);
			addToLeaf(root->right, res, sum);
		}
	}

	/*
	* Leetcode #199：Binary Tree Right Side View
	* 返回一棵树的右视图
	* 使用一个vector<TreeNode *> Node存下每层的所有节点
	*/
	vector<int> rightSideView(TreeNode* root) {
		vector<int> res;
		if (root == NULL)
			return res;
		TreeNode* start = root;
		res.push_back(root->val);
		vector<TreeNode *> Node;
		Node.push_back(root);
		int size = 0;
		while (1){
			size = Node.size();
			for (int i = 0; i<size; i++){
				if (Node[0]->left != NULL)
					Node.push_back(Node[0]->left);
				if (Node[0]->right != NULL)
					Node.push_back(Node[0]->right);
				Node.erase(Node.begin());
			}
			if (Node.empty())
				return res;
			res.push_back(Node[Node.size() - 1]->val);		//存入最右边的数
		}
	}
	
	/*
	* 输入两颗二叉树A，B，判断B是不是A的子结构
	*/
        bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2){
        	if(pRoot2==NULL)
            		return false;
		if((pRoot1==NULL&&pRoot2!=NULL))
            		return false;
        	if((pRoot1==NULL&&pRoot2==NULL))
            		return false;
        	if(pRoot1->val==pRoot2->val){
            		if(Check(pRoot1,pRoot2))
                		return true;
        	}
        	return HasSubtree(pRoot1->left,pRoot2)||HasSubtree(pRoot1->right,pRoot2);
    }
    
    	bool Check(TreeNode* pRoot1, TreeNode* pRoot2){
        	if((pRoot1==NULL&&pRoot2!=NULL))
            		return false;
        	if(pRoot2==NULL)
            		return true;
        	if(pRoot1->val!=pRoot2->val)
            		return false;
        	return Check(pRoot1->left,pRoot2->left)&&Check(pRoot1->right,pRoot2->right);
    }
        
        
	/*max()  min()函数*/
	int max(int a, int b){
		return a > b ? a : b;
	}

	int min(int a, int b){
		return a < b ? a : b;
	}
	/*end of class myTree*/
}
