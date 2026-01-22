//https://leetcode.cn/problems/max-submatrix-lcci/description/
//https://www.bilibili.com/video/BV1pw411M7Du?t=4607.2

//压缩数组的方式,
//必须包含0~0行数字,在合并之后的一维数组中选择连续最大子数组即可
//       0~1
//      ...
//       0~n-1
//       1~1
//       ...
//       1~n-1
//...
//以上压缩数组求解记录最大值
//枚举的过程就是O(n^2)
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
	vector<int> getMaxMatrix(vector<vector<int>>& matrix)
	{
		int n = matrix.size();
		int m = matrix[0].size();
		int maxVal = INT_MIN;
		int a = 0, b = 0, c = 0, d = 0;
		for (int up = 0; up < n; up++)
		{
			vector<int>nums(m);
			for (int down = up; down < n; down++)
			{
				int prev = INT_MIN;
				for (int l = 0, r = 0; r < m; r++)
				{
					nums[r] += matrix[down][r];
					if (prev < 0)
					{
						prev = nums[r];
						l = r;
					}
					else
						prev += nums[r];
					if (prev > maxVal)
					{
						maxVal = prev;
						a = up;
						b = l;
						c = down;
						d = r;
					}
				}
			}
		}
		return { a,b,c,d };
	}
};