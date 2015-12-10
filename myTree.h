/*
* Part of the questions here is from leetcode(https://leetcode.com/).
*
*/

#include "head.h"
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

}
