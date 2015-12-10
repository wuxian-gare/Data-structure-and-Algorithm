/*
* 头文件使用示例
*/

#include "myVector.h"
#include "myTree.h"

int main(){
  vector<int> test = {1,0,1,1,1};
  MyVector myVec;
  cout<<myVec.minNumberInRotateArray(test);

	vector<int> test = { 1, 2, 3, 4,0, 5, 6,0, 7};
	myTree myTree;
	TreeNode *root;
	root=s.createTree(test);
	
	myTree.postOrder_1(root);
	myTree.postOrder_2(root);
	myTree.postOrder_3(root);
	myTree.preOrder(root);
	myTree.inOrder(root);
	myTree.morris_inorder_traversal(root);
	cout << "LCA:" << myTree.findLCA(root, 4, 6) << endl;

	int a[10] = { 197, 167, 182, 157, 194, 199, 193, 124, 153, 186 };
	mySort res;
	res.sort(a,10);
	res.countSort(a, 10, 2);

	vector<int> tr = { 1, 2, 5, 3, 4, 6,7};
	TreeNode *root;
	root=myTree.sortedArrayToBST(tr);
	root=myTree.createTree(tr);
	cout << "create success ." << endl;
	myTree.inOrder(root);
	myTree.flatten(root);
	myTree.preOrder(root);
	system("pause");
    return 0;
}
