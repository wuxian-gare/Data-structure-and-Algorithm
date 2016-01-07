/*
* vector相关算法
*
*/

#include "head.h"
using namespace std;

class MyVector{
public:
int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size() == 0)
            return 0;
        if(rotateArray.size() == 1)
            return rotateArray[0];
        if(rotateArray[0]<rotateArray.back())
            return rotateArray[0];

        int start = 0,end = rotateArray.size() - 1;
        int mid;
        while(end - start>1){
            mid = (start + end) / 2;
            if(rotateArray[mid] == rotateArray[end] && rotateArray[mid] == rotateArray[start]){
                int i = start;
                for(i = start+1;i <= end;i++){
                    if(rotateArray[i] < rotateArray[i - 1])
                        return rotateArray[i];
                }
            }
            if(rotateArray[mid]>rotateArray[end]){
                start = mid;
                continue;
            }
            else{
                end = mid;
                continue;
            }
        }
        return rotateArray[end];
    }

	/*
	*Leetcode #77:	Combinations
	*
	* Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
  *
	* For example,
	If n = 4 and k = 2, a solution is:

	[
	  [2,4],
	  [3,4],
	  [2,3],
	  [1,2],
	  [1,3],
	  [1,4],
	]
	*/
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> res;
		vector<int> s;
		if (n<1 || k<1 || n<k)
			return res;
		for (int i = 1; i <= n; i++)
			insert(res, k, i, n, s);
		return res;
	}
	void insert(vector<vector<int>> &res, int count, int start, int n, vector<int> s){
		if (count == 0){
			res.push_back(s);
			return;
		}
		else{
			if (start>n)
				return;
			s.push_back(start);
			if (count == 1){			//已经是最后一个   加这一部分是为了避免重复
				res.push_back(s);
				return;
			}
			while (start <= n){
				insert(res, count - 1, ++start, n, s);
			}
		}
	}

	/*
	*Leetcode #238: Product of Array Except Self
	*/
	vector<int> productExceptSelf(vector<int>& nums) {
		int pre = nums[0];
		int next = nums[1];
		int count = 0;
		int offset = 0;
		for (int i = 0; i<nums.size(); i++){
			if (nums[i] == 0){
				count++;
				offset = i;
			}
		}
		if (count>1){
			nums.assign(nums.size(), 0);
		}
		else if (count == 1){
			int temp = 1;
			for (int j = 0; j<nums.size(); j++){
				if (offset == j)
					continue;
				temp *= nums[j];
			}
			nums.assign(nums.size(), 0);
			nums[offset] = temp;
		}
		else{
			nums[0] = 1;
			for (int i = 1; i<nums.size(); i++){
				nums[0] *= nums[i];
			}
			for (int i = 1; i<nums.size(); i++){
				next = nums[i];
				nums[i] = nums[i - 1] * pre / nums[i];
				pre = next;
			}
		}
		return nums;
	}

	/*
	*不太好的算法
	*Leetcode #42: Trapping Rain Water
	*/
	int trap(vector<int>& height) {
		if (height.size()<3)
			return 0;
		int max = height[0];
		int begin = 0;
		int left = -1, right = -1;
		int sum = 0;
		for (int i = 1; i<height.size(); i++){
			if (height[i]>max)
				max = height[i];
			if (height[i] == 0)
				begin++;
		}
		for (int level = 1; level <= max; level++){
			for (int j = begin + 1; j<height.size(); j++){
				if (height[j]<level){
					for (int k = j + 1; k<height.size(); k++){
						if (height[k] >= level){
							sum += k - j;
							break;
						}
					}


				}
			}
		}
		return sum;
	}

	/*
	*Leetcode #300:	Longest Increasing Subsequence
	*最长递增子序列
	*http://yzmduncan.iteye.com/blog/1546503
	*/
	int lengthOfLIS(vector<int>& nums) {
		if (nums.size()<2)
			return nums.size();
		int i = 0, j = 0;
		vector<int> d;
		d.push_back(nums[0]);
		int len = 0;        //递增子序列长度  
		for (i = 1; i < nums.size(); i++)  {
			if (d[len]<nums[i]){
				d.push_back(nums[i]);
				len++;
			}
			else{
				j = BinSearch(nums[i], d, len);
				d[j] = nums[i];
			}
		}
		return len + 1;
	}
	/*
	*二分查找
	*/
	int BinSearch(int key, vector<int>& d, int high){
		if (high == 0)
			return 0;
		int low = 0;
		while (low <= high){
			int mid = (low + high) >> 1;
			if (key>d[mid] && key <= d[mid + 1])
				return mid + 1;
			else if (key>d[mid])
				low = mid + 1;
			else
				high = mid - 1;
		}
		return 0;
	}

	/*
	*
	*Leetcode #153:	Find Minimum in Rotated Sorted Array
	*/
	int findMin(vector<int>& nums) {
		int low = 0, high = nums.size() - 1, mid = 0;
		if (high == -1)
			return 0;
		if (high == 0)
			return nums[0];
		if (nums[high]>nums[low])
			return nums[low];
		while (low != high - 1){
			mid = (low + high) >> 1;
			if (nums[mid]>nums[low])
				low = mid;
			else
				high = mid;
		}
		return nums[high];
	}

	/*
	*Leetcode #62:	Unique Paths
	*/
	int uniquePaths(int m, int n) {
		if (m<1 || n<1)
			return 0;
		int i = 0, j = 0;
		//int res[m][n];
		int **res = new int*[m];
		for (int i = 0; i < n; i++)
			res[i] = new int[n];

		for (i = 0; i<n; i++)
			res[0][i] = 1;
		for (i = 1; i<m; i++)
			res[i][0] = 1;
		cout << res[1][0];
		for (i = 1; i<m; i++)
		for (j = 1; j<n; j++)
			res[i][j] = res[i - 1][j] + res[i][j - 1];
		return res[m - 1][n - 1];

	}

	/*
	*Leetcode #89：	第一种格雷码产生方式，循环更改置位
	*/
	vector<int> grayCode(int n) {
		vector<int> res;
		if (n<1){
			res.push_back(0);
			return res;
		}
		if (n == 1){
			res.push_back(0);
			res.push_back(1);
			return res;
		}
		int i = 0;
		int flag = 1;
		int temp = 0;
		int patt = 0;
		do{
			res.push_back(temp);
			i += flag;
			patt = (n - i - 1) << 1;
			if (i == 0)
				flag = 1;
			if (i == n - 1){
				patt = 1;
				flag = -1;
			}
			cout << "**" << patt << endl;
			temp = temp^patt;
		} while (temp != 0);
		return res;
	}

	/*
	*Leetcode #89：	第二种格雷码，动态规划
	*/
	vector<int> grayCode_2(int n) {
		vector<int> res;
		res.push_back(0);
		if (n<1)
			return res;
		res.push_back(1);
		int size = 0;
		int i = 1;
		for (i = 1; i<n; i++){
			size = 1 << i;
			cout << "size is :" << size << endl;
			for (int j = size - 1; j >= 0; j--){
				res.push_back(res[j] + size);
			}
		}
		return res;
	}

	/*
	* Leetcode #22 : Generate Parentheses
	* 输入一个整数n,输出n个括号的所有可能组合
	* 第一种是非递归解法：
	* 做法是：先插入一个（，每当要选择时，就将 ~ + “）”push_back，然后将 ~ + “（”
	*/
	vector<string> generateParenthesis(int n) {
		vector<string> res;
		if (n<1)
			return res;
		res.push_back("(");
		int count = 1, count_A = 1, count_B = 0;
		int i = 0, j = 0;
		int offset = 0;
		while (i != res.size()){
			cout << "第" << "i" << "个： " << count_A << "  " << count_B << endl;
			count = count_A - count_B;
			if (count == 0 && count_A<n){
				res[i] = res[i] + "(";
				count_A++;
				continue;
			}
			else if (count == 0 && count_A == n){
				return res;
			}
			else if (count_A == n){
				for (j = 0; j<n - count_B; j++)
					res[i] += ")";
				i++;
				if (i == res.size())
					return res;
				count_A = 0;
				count_B = 0;
				for (j = 0; j<res[i].size(); j++){
					if (res[i][j] == '(')
						count_A++;
					else
						count_B++;
				}
				continue;
			}
			else{
				res.push_back(res[i] + ")");
				res[i] += "(";
				count_A++;
				continue;
			}
		}
		return res;
	}

	/*
	* Leetcode #22：	递归解法如下：
	* 可以理解为，m,n分别代表剩下的“（”、“）”个数
	* 当m,n都是0时，将其push_back
	*/
	void unguarded_generate(vector<string> &result, string curr, int m, int n)
	{
		if (m == 0 && n == 0)
		{
			result.push_back(curr);
		}
		else
		{
			if (m != 0)
			{
				unguarded_generate(result, curr + "(", m - 1, n);
			}

			if (m < n && n != 0)
			{
				unguarded_generate(result, curr + ")", m, n - 1);
			}
		}
	}

	vector<string> generateParenthesis_2(int n)
	{
		vector<string> ret;

		if (n > 0)
		{
			unguarded_generate(ret, string(), n, n);
		}

		return ret;
	}

	/*
	* Leetcode #75:	Sort Colors
	* 有限取值的数组排序
	* 用i，j记下最后的0,1位置
	*/
	void sortColors(vector<int> &A) {
		int i = -1, j = -1;
		for (int p = 0; p < A.size(); p++) {

			int v = A[p];
			A[p] = 2;
			if (v == 0) {
				A[++j] = 1;
				A[++i] = 0;
			}
			else if (v == 1) {
				A[++j] = 1;
			}
		}
	}

	/*
	* Leetcode #46：	Permutations
	* 给[1,2,3]，返回所有排列组合(全排列问题)
	* <1> 自己写的递归
	*/
	vector<vector<int>> permute1(vector<int>& nums) {
		vector<vector<int>> ans;
		int size = nums.size();
		if (size<1)
			return ans;
		int i = 0;
		for (i = 0; i<size; i++){
			vector<int> temp = getVec(nums, i);
			vector<vector<int>> res = permute1(temp);
			if (res.empty()){						//得到结果为空，表示已经到头
				vector<int> qwe;
				res.push_back(qwe);
				res[0].push_back(nums[i]);
				ans.push_back(res[0]);
				qwe.clear();
			}
			else{
				for (int j = 0; j<res.size(); j++){
					res[j].push_back(nums[i]);
					ans.push_back(res[j]);
				}
			}
			temp.clear();
			res.clear();
		}
		return ans;
	}

	vector<int> getVec(vector<int>& nums, int i){			//将该元素去掉
		vector<int> temp = nums;
		temp.erase(temp.begin() + i);
		return temp;
	}


	/*
	* <2>利用深度优先递归
	*/
	vector<vector<int> > permute2(vector<int> &num) {
		vector<vector<int> > ret;
		dfs(ret, num, 0);
		return ret;
	}

	void dfs(vector<vector<int> >& ret, vector<int>& num, int cur)
	{
		if (num.size() == cur){				//当交换到最后时，将结果push_back
			ret.push_back(num);
		}
		else{
			for (int i = cur; i < num.size(); ++i){
				swap(num[cur], num[i]);							//逐个交换
				dfs(ret, num, cur + 1);
				swap(num[cur], num[i]);							//将数组还原
			}
		}
	}

	/*
	* Leetcode #74：	Search a 2D Matrix
	*/
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty())
			return false;
		int row = matrix.size();
		int i = 0;
		for (i = 0; i<row - 1; i++){
			if (matrix[i][0] <= target&&matrix[i + 1][0]>target){
				return check(matrix[i], target);
			}
			else{
				continue;
			}
		}
		int line = matrix[i].size();
		if (matrix[i][line - 1]<target)
			return false;
		else
			return check(matrix[i], target);
	}

	/*
	*	二分查找
	*/
	bool check(vector<int> res, int target){
		int end = res.size() - 1;
		int start = 0;
		if (target<res[start] || target>res[end])
			return false;
		int mid = 0;
		while (start != end - 1 && start != end){
			mid = (start + end) >> 1;
			if (res[mid] == target)
				return true;
			if (res[mid]>target)
				end = mid;
			if (res[mid]<target)
				start = mid;
		}
		if (res[start] == target || res[end] == target)
			return true;
		else
			return false;
	}


	/*
	* Leetcode #48：	Rotate Image
	* 将一张图片（矩阵）顺时针翻转90度
	* 做法：先上下翻转，再对角翻转
	*/
	void rotate(vector<vector<int>>& matrix) {
		int n = matrix.size() - 1;
		/*上下翻转*/
		for (int i = 0; i<(n + 1) / 2; i++){
			for (int j = 0; j <= n; j++){
				swap(matrix[i][j], matrix[n - i][j]);
			}
		}
		/*对角翻转*/
		for (int i = 0; i <= n; i++){
			for (int j = 0; j<i; j++){
				swap(matrix[i][j], matrix[j][i]);
			}
		}

	}

	/*
	* Leetcode #59：	Spiral Matrix II
	* 旋转矩阵
	* 方法一、公式推导法--如下
	* 方法二、创建矩阵，旋转赋值
	*/
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> res;
		if (n<1)
			return res;
		vector<int> temp;
		temp.reserve(n);
		int val = 0;
		int circle = 0;
		int *start = new int[(n + 1) / 2];
		start[0] = 1;
		for (int i = 1; i<(n + 1) / 2; i++)
			start[i] = start[i - 1] + 4 * (n - 2 * i + 1);			//第i圈的起始数值
		for (int i = 0; i<n; i++){
			temp.clear();
			res.push_back(temp);
			for (int j = 0; j<n; j++){
				circle = min(min(i, j), min(n - i - 1, n - j - 1));			//计算第几圈
				if (i <= j){
					val = start[circle] + i + j - 2 * circle;
				}
				else{
					val = start[circle] + 4 * (n - circle - 1) - i - j - 2 * circle;
				}
				res[i].push_back(val);
			}
		}
		return res;
	}

	/*
	* Leetcode #162：	Find Peak Element
	* A peak element is an element that is greater than its neighbors.
	*
	* Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.
	*
	* The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
	*
	* You may imagine that num[-1] = num[n] = -∞.
	*
	* For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.
	*/
	int findPeakElement(vector<int>& nums) {
		int flag = 1;
		int size = nums.size();
		for (int i = 0; i<size - 1; i++){
			if (nums[i + 1]<nums[i]){
				if (flag == 1)
					return i;
				else
					flag = 0;
			}
			else
				flag = 1;
		}
		return size - 1;
	}

	/*
	* Leetcode #78：	Subsets
	* 给定一个集合，返回所有子集（包括空集和自身）
	* 解法一：DFS，深度优先
	*/
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> res;
		vector<int> temp;
		res.push_back(temp);
		int size = nums.size();
		//当要求结果严格有序时，可以先排序
		sort(nums.begin(), nums.end());
		for (int i = 1; i <= size; i++){
			temp.clear();
			addSub(res, nums, temp, 0, i);
		}
		return res;
	}
	void addSub(vector<vector<int>>&res, vector<int>& nums, vector<int> temp, int start, int count){
		if (count == 0){
			res.push_back(temp);
			return;
		}
		if (start >= nums.size())
			return;
		addSub(res, nums, temp, start + 1, count);			//不包含自身的情况，count不变
		temp.push_back(nums[start]);
		count--;
		if (count == 0){									//避免出现重复  一旦完成就不再执行
			res.push_back(temp);
			return;
		}
		addSub(res, nums, temp, start + 1, count);
	}

	/*
	* 第二种方法：位运算
	*/
	vector<vector<int> > subsets(vector<int> &S)
	{
		int n = S.size();
		//n个数有0~max-1即2^n中组合，1<<n表示2^n
		int max = 1 << n;
		vector<vector<int> >result;
		for (int i = 0; i < max; i++)
		{
			vector<int> temp;
			int idx = 0;
			int j = i;
			while (j > 0)
			{
				//判断最后一位是否为1，若为1则将对应数加入到当前组合中
				if (j & 1)
				{
					temp.push_back(S[idx]);
				}
				idx++;
				//判断了这一位是否为1后要右移
				j = j >> 1;
			}
			//判断完了一种组合，加入到结果集中
			result.push_back(temp);
		}
		return result;
	}
	/*
	* 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。
	* 假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4，5,3,2,1是该
	* 压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
	*/
        bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        	stack<int> res;
        	int offset=0;
        	int pos=0;
        	while(1){
        	    if(res.empty()||res.top()!=popV[offset]){
        	       if(pushV.size()==pos)
        	            return false;
                	res.push(pushV[pos]);
                	pos++;
                	continue;
            	    }
            	    else{
                  	    offset++;
                	    if(offset==popV.size())
                    		    return true;
                	    res.pop();
            	    }
        	}	
    	}



	/*end of class myVector*/
	int max(int a, int b){
		return a > b ? a : b;
	}

	int min(int a, int b){
		return a < b ? a : b;
	}
}
